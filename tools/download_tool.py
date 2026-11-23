#!/usr/bin/env python3
"""Download and cache pinned build tools defined in tools/tools.toml."""

import argparse
import functools
import hashlib
import http.client
import json
import os
import platform
import shutil
import stat
import sys
import tarfile
import tempfile
import tomllib
import urllib.error
import urllib.parse
import urllib.request
import zipfile
from dataclasses import dataclass, field
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parent.parent
MANIFEST = ROOT / "tools" / "tools.toml"
TOOLS_DIR = ROOT / "build" / "tools"


@dataclass(frozen=True)
class Tool:
    """Metadata and resolved cache paths for a tool entry in tools.toml."""

    name: str
    version: str
    exe: str
    strip: int = 0
    format: str | None = None
    url: str | None = None
    sha256: str | None = None
    platforms: dict[str, dict[str, str]] = field(default_factory=dict)

    def cache_key(self):
        """Return a short hash of the tool configuration for cache invalidation."""
        spec = {
            "version": self.version,
            "exe": self.exe,
            "strip": self.strip,
            "format": self.format,
            "url": self.url,
            "sha256": self.sha256,
            "platforms": self.platforms,
        }
        raw = json.dumps(spec, sort_keys=True).encode()
        return hashlib.sha256(raw).hexdigest()[:8]

    @property
    def install_dir(self):
        """Return the versioned and config-hashed installation directory."""
        # Hash the full entry so url/sha256/strip edits invalidate cached dirs.
        return TOOLS_DIR / f"{self.name}-{self.version}-{self.cache_key()}"

    @property
    def exe_path(self):
        """Return the expected executable path inside the installation directory."""
        return self.install_dir / self.exe


def _parse_tool(name, entry):
    """Construct a Tool instance from a parsed TOML table."""
    return Tool(
        name=name,
        version=entry["version"],
        exe=entry["exe"],
        strip=entry.get("strip", 0),
        format=entry.get("format"),
        url=entry.get("url"),
        sha256=entry.get("sha256"),
        platforms=entry.get("platforms", {}),
    )


@functools.cache
def load_tools():
    """Load and cache all tool definitions from tools/tools.toml."""
    with MANIFEST.open("rb") as f:
        raw = tomllib.load(f)
    return {name: _parse_tool(name, entry) for name, entry in raw.items()}


def get_tool(name):
    """Look up a tool by name or exit if it is not defined."""
    tools = load_tools()
    if name not in tools:
        sys.exit(
            f"download_tool: Unknown tool {name!r}. "
            f"Available tools: {', '.join(tools)}."
        )
    return tools[name]


def resolve_override(value):
    """Resolve a user-supplied executable override from PATH or the filesystem."""
    if "/" not in value and os.sep not in value and (found := shutil.which(value)):
        return Path(found)
    return Path(value).expanduser().resolve()


def tool_exe(name, *, override=None):
    """Return the executable path for a tool without downloading it."""
    if override is not None:
        return resolve_override(override)
    return get_tool(name).exe_path


def _host_platform():
    """Return the normalized '<os>-<arch>' key matching tools.toml."""
    system = {"Linux": "linux", "Darwin": "macos"}.get(platform.system())
    if system is None:
        sys.exit(f"download_tool: Unsupported host system: {platform.system()}.")
    machine = platform.machine().lower()
    if machine in ("amd64", "x86_64"):
        machine = "x86_64"
    elif machine in ("arm64", "aarch64"):
        # Upstream release names differ: macOS uses arm64, Linux uses aarch64.
        machine = "arm64" if system == "macos" else "aarch64"
    return f"{system}-{machine}"


def _resolve_source(tool):
    """Select the download URL and expected SHA-256 digest for the host."""
    if tool.url is not None and tool.sha256 is not None:
        return tool.url, tool.sha256
    host = _host_platform()
    if host not in tool.platforms:
        if tool.platforms:
            available = ", ".join(tool.platforms)
            sys.exit(
                f"download_tool: No prebuilt binary is available for {host} "
                f"(available platforms: {available})."
            )
        sys.exit(
            "download_tool: No download URL or platforms are configured "
            f"for {tool.name}."
        )
    entry = tool.platforms[host]
    return entry["url"], entry["sha256"]


def _detect_format(tool, url):
    """Determine whether the payload is a zip archive, tar archive, or binary."""
    if tool.format is not None:
        if tool.format not in ("zip", "tar", "bin"):
            sys.exit(
                f"download_tool: Unknown archive format {tool.format!r} "
                f"for {tool.name}."
            )
        return tool.format
    path = urllib.parse.urlsplit(url).path
    if path.endswith(".zip"):
        return "zip"
    if path.endswith((".tar.gz", ".tgz", ".tar.xz", ".tar.bz2")):
        return "tar"
    return "bin"


def _strip_components(path, count):
    """Drop leading directory components from an archive member path."""
    parts = PurePosixPath(path).parts[count:]
    return Path(*parts) if parts else None


def _extract_zip(archive_path, dest, strip):
    """Extract a zip archive into dest while enforcing path containment."""
    dest_resolved = dest.resolve()
    with zipfile.ZipFile(archive_path) as archive:
        for info in archive.infolist():
            rel = _strip_components(info.filename, strip)
            if rel is None or info.is_dir():
                continue
            out = dest / rel
            if not out.resolve().is_relative_to(dest_resolved):
                sys.exit(f"download_tool: Unsafe path in archive: {info.filename}.")
            out.parent.mkdir(parents=True, exist_ok=True)
            out.write_bytes(archive.read(info))
            mode = (info.external_attr >> 16) & 0o777
            if mode:
                out.chmod(mode)


def _extract_tar(archive_path, dest, strip):
    """Extract a tar archive into dest with leading path components stripped."""
    with tarfile.open(archive_path) as archive:
        members = []
        for member in archive.getmembers():
            rel = _strip_components(member.name, strip)
            if rel is None:
                continue
            member.name = rel.as_posix()
            if member.islnk():
                # Hardlink targets are archive-root-relative, unlike symlinks.
                link_rel = _strip_components(member.linkname, strip)
                if link_rel is None:
                    continue
                member.linkname = link_rel.as_posix()
            members.append(member)
        archive.extractall(dest, members=members, filter="data")


def _fetch(url, fd):
    """Download url into an open file descriptor and return its SHA-256 digest."""
    request = urllib.request.Request(url, headers={"User-Agent": "download_tool.py"})
    hasher = hashlib.sha256()
    try:
        with (
            os.fdopen(fd, "wb") as out,
            urllib.request.urlopen(request, timeout=60) as response,
        ):
            while chunk := response.read(65536):
                hasher.update(chunk)
                out.write(chunk)
    except (urllib.error.URLError, http.client.HTTPException, TimeoutError) as err:
        detail = str(err).rstrip(".")
        sys.exit(f"download_tool: Failed to fetch {url}: {detail}.")
    return hasher.hexdigest()


def ensure_tool(name, *, override=None):
    """Download the tool if needed and return its executable path."""
    if override is not None:
        return resolve_override(override)
    tool = get_tool(name)
    final = tool.install_dir
    if final.exists():
        return tool.exe_path

    url, sha256 = _resolve_source(tool)
    print(
        f"download_tool: Fetching {tool.name} ({tool.version}) from {url}.",
        file=sys.stderr,
    )

    TOOLS_DIR.mkdir(parents=True, exist_ok=True)
    tmp_dir = Path(tempfile.mkdtemp(prefix=f".{tool.name}-", dir=TOOLS_DIR))
    archive_fd, archive_raw = tempfile.mkstemp(prefix=f".{tool.name}-", dir=TOOLS_DIR)
    archive_path = Path(archive_raw)
    try:
        digest = _fetch(url, archive_fd)
        if digest != sha256.lower():
            sys.exit(
                f"download_tool: SHA-256 mismatch for {tool.name}.\n"
                f"  Expected: {sha256}\n"
                f"  Actual:   {digest}"
            )

        fmt = _detect_format(tool, url)
        if fmt == "zip":
            _extract_zip(archive_path, tmp_dir, tool.strip)
        elif fmt == "tar":
            _extract_tar(archive_path, tmp_dir, tool.strip)
        else:
            out = tmp_dir / tool.exe
            out.parent.mkdir(parents=True, exist_ok=True)
            archive_path.replace(out)

        exe = tmp_dir / tool.exe
        if not exe.exists():
            sys.exit(
                f"download_tool: Expected executable {tool.exe!r} was not found "
                f"in the {tool.name} download."
            )
        exe.chmod(exe.stat().st_mode | stat.S_IXUSR | stat.S_IXGRP | stat.S_IXOTH)
        # mkdtemp defaults to 0700; restore normal permissions before rename.
        tmp_dir.chmod(0o755)
        try:
            tmp_dir.rename(final)
        except OSError:
            if not (final.exists() and tool.exe_path.exists()):
                raise
    finally:
        archive_path.unlink(missing_ok=True)
        shutil.rmtree(tmp_dir, ignore_errors=True)
    return tool.exe_path


def main():
    """Parse CLI arguments and install or query the requested tool."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("name", help="Name of the tool to download from tools/tools.toml.")
    parser.add_argument(
        "--stamp",
        type=Path,
        help="Path to a stamp file to touch after the tool is installed.",
    )
    parser.add_argument(
        "--print-exe",
        action="store_true",
        help="Print the resolved executable path to standard output.",
    )
    args = parser.parse_args()
    exe = ensure_tool(args.name)
    if args.stamp:
        args.stamp.parent.mkdir(parents=True, exist_ok=True)
        args.stamp.touch()
    if args.print_exe:
        print(exe)


if __name__ == "__main__":
    main()