#!/usr/bin/env python3
"""Generate build.ninja and objdiff.json for building the ROM.

On a clean tree before splat has generated the linker script, this writes a
bootstrap build.ninja that decompresses and splits the baserom, then re-runs
configure.py automatically.
"""

import argparse
import io
import json
import os
import re
import shlex
import shutil
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

import ninja_syntax
import yaml

from tools import download_tool

ROOT = Path(__file__).resolve().parent
BASENAME = "mnsg"

ULTRALIB_DIR = "lib/ultralib"

INCLUDES = [
    "-Iinclude",
    f"-I{ULTRALIB_DIR}/include",
    f"-I{ULTRALIB_DIR}/include/PR",
    f"-I{ULTRALIB_DIR}/include/compiler/ido",
    "-Isrc",
    "-I.",
]
DEFINES = [
    "-D_LANGUAGE_C",
    "-D_FINALROM",
    "-DF3DEX_GBI",
    "-D__sgi",
    "-DNDEBUG",
    "-DBUILD_VERSION=VERSION_I",
    '-DBUILD_VERSION_STRING="2.0I"',
]
CFLAGS = [
    "-G",
    "0",
    "-non_shared",
    "-Xfullwarn",
    "-Xcpluscomm",
    *INCLUDES,
    "-Wab,-r4300_mul",
    "-woff",
    "649,838,712",
    *DEFINES,
]
OPTFLAGS = ["-O2"]
MIPSISA = ["-mips2"]
OPTFLAGS_OVERRIDES = {
    "src/sys/bit.c": ["-O2", "-g3"],
    "src/sys/is_debug.c": ["-O2", "-g3"],
}
CHECK_FLAGS = [
    "-m32",
    "-fno-builtin",
    "-fsyntax-only",
    "-fsigned-char",
    "-std=gnu90",
    *DEFINES,
    "-Wall",
    "-Wextra",
    "-Wno-format-security",
    "-Wno-unknown-pragmas",
    "-Wno-unused-parameter",
    "-Wno-unused-variable",
    "-Wno-missing-braces",
    "-Wno-int-conversion",
    "-Wno-unterminated-string-initialization",
    "-Wno-unused-value",
    *INCLUDES,
]
ASFLAGS = ["-EB", "-mtune=vr4300", "-march=vr4300", "-mabi=32", "-Iinclude", "-I."]

ULTRALIB_ARCHIVE = f"{ULTRALIB_DIR}/build/I/libultra_rom/libultra_rom.a"
LIBULTRA_ARCHIVE = "build/usa/lib/libultra_rom.a"

ENCODING = "Shift_JIS"
ENCODING_OVERRIDES = {
    "usa": {
        "asm/usa/data/file_32.rodata.s": "EUC-JP",
        "asm/usa/data/file_44.rodata.s": "EUC-JP",
        "asm/usa/data/file_59.rodata.s": "EUC-JP",
    },
}

CROSS_PREFIXES = ("mips-linux-gnu-", "mips64-linux-gnu-", "mips64-elf-")
PREFERRED_LD_EMULATIONS = ("elf32btsmip", "elf32ebmip")


@dataclass(frozen=True)
class BuildPaths:
    """Resolved input and output paths for a specific ROM version."""

    version: str
    config_dir: Path
    build_dir: str
    yaml: Path
    ld_script: Path
    undefined_lds: list[Path]
    baserom: Path
    decompressed: Path
    manifest: Path
    split_stamp: str

    @classmethod
    def for_version(cls, version):
        """Construct the build path layout for the given game version."""
        config_dir = Path("config") / version
        splat_dir = Path(".splat") / version
        build_dir = f"build/{version}"
        return cls(
            version=version,
            config_dir=config_dir,
            build_dir=build_dir,
            yaml=config_dir / "splat.yaml",
            ld_script=splat_dir / f"{BASENAME}.ld",
            undefined_lds=[
                splat_dir / "undefined_syms_auto.ld",
                splat_dir / "undefined_funcs_auto.ld",
            ],
            baserom=config_dir / "baserom.z64",
            decompressed=config_dir / "baserom.decompressed.z64",
            manifest=config_dir / "rommy.yaml",
            split_stamp=f"{build_dir}/split.stamp",
        )


def parse_args():
    """Parse command-line options for configuring the build."""
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        "--version",
        default="usa",
        help="Game version to configure (default: usa).",
    )
    parser.add_argument(
        "--compressed",
        action="store_true",
        help="Build the compressed ROM image.",
    )
    parser.add_argument(
        "--cross",
        help=(
            "MIPS binutils prefix "
            f"(default: first available of {', '.join(CROSS_PREFIXES)})."
        ),
    )
    parser.add_argument(
        "--ld-emulation",
        help="Override the GNU ld -m emulation mode (pass '' to omit -m).",
    )
    parser.add_argument(
        "--tool",
        action="append",
        default=[],
        metavar="NAME=PATH",
        help="Override a tool executable from tools/tools.toml (repeatable).",
    )
    parser.add_argument(
        "--host-cc",
        default=os.environ.get("HOST_CC") or "gcc",
        help="Host C compiler for syntax checks (default: $HOST_CC or gcc).",
    )
    parser.add_argument(
        "--no-check",
        action="store_true",
        help="Skip host C syntax checks before invoking IDO.",
    )
    return parser.parse_args()


def parse_tool_overrides(entries, tools):
    """Parse and validate '--tool NAME=PATH' overrides against tools.toml."""
    overrides = {}
    for entry in entries:
        if "=" not in entry:
            sys.exit(
                f"configure: Invalid --tool argument {entry!r}; expected NAME=PATH."
            )
        name, value = entry.split("=", 1)
        if name not in tools:
            sys.exit(
                f"configure: Unknown tool {name!r} passed to --tool. "
                f"Available tools: {', '.join(tools)}."
            )
        if not value:
            sys.exit(f"configure: Empty path provided for --tool {name}=.")
        overrides[name] = value
    return overrides


def find_cross(prefix):
    """Locate a MIPS cross-binutils prefix on PATH."""
    candidates = (prefix,) if prefix is not None else CROSS_PREFIXES
    for candidate in candidates:
        if shutil.which(f"{candidate}ld"):
            return candidate
    if prefix is not None:
        sys.exit(f"configure: Cross-compiler '{prefix}ld' was not found in PATH.")
    sys.exit(
        "configure: No MIPS binutils were found in PATH "
        f"(tried {', '.join(CROSS_PREFIXES)}). Install a toolchain or pass --cross."
    )


def detect_ld_emulation(cross):
    """Probe GNU ld for a supported 32-bit big-endian MIPS emulation."""
    # GNU ld lists supported emulations in `ld -V`; prefer o32 big-endian
    # regardless of whether the toolchain defaults to 64-bit or n32.
    result = subprocess.run(
        [f"{cross}ld", "-V"],
        capture_output=True,
        text=True,
        check=False,
    )
    tokens = set((result.stdout + "\n" + result.stderr).split())
    for emu in PREFERRED_LD_EMULATIONS:
        if emu in tokens:
            return emu
    return None


def linker_objects(ld_script, build_dir):
    """Extract unique object-to-source pairs from the linker script in order."""
    # Splat references each .o once per section (.text, .data, ...); keep unique
    # entries in link order.
    pattern = re.compile(rf"\b({re.escape(build_dir)}/(\S+?)\.o)\(")
    objects = {}
    for match in pattern.finditer(ld_script.read_text()):
        obj, src = match.groups()
        if ":" in src:
            # A member of an archive (splat's lib segments); linked from the archive instead.
            continue
        objects.setdefault(obj, src)
    return objects


def splat_deps(yaml_path):
    """Return auxiliary symbol and relocation files referenced by splat.yaml."""
    if not yaml_path.exists():
        sys.exit(f"configure: Splat configuration file not found: {yaml_path}.")
    opts = yaml.safe_load(yaml_path.read_text()).get("options") or {}
    deps = []
    for key in ("symbol_addrs_path", "reloc_addrs_path"):
        value = opts.get(key) or []
        if isinstance(value, str):
            value = [value]
        deps.extend(Path(path) for path in value)
    return deps


def emit_bootstrap(ninja, paths, tools, overrides):
    """Emit tool download, ROM decompression, splat split, and reconfigure rules."""
    # generator=True stops `ninja -t clean` from removing downloaded tools and
    # split ROM assets.
    ninja.rule(
        "download",
        "$python tools/download_tool.py $name --stamp $out",
        description="DOWNLOAD $name",
        generator=True,
    )
    tool_stamps = {}
    for name, tool in tools.items():
        if name in overrides:
            continue
        stamp = f"build/tools/{name}-{tool.version}-{tool.cache_key()}.stamp"
        ninja.build(
            stamp, "download", implicit=["tools/tools.toml"], variables={"name": name}
        )
        tool_stamps[name] = stamp
    ninja.build("tools", "phony", list(tool_stamps.values()))
    ninja.newline()

    ninja.rule(
        "decompress",
        "$python tools/rommy.py decompress --input $in --output $out"
        " --manifest $manifest --pad",
        description="DECOMPRESS $in",
        generator=True,
    )
    ninja.build(
        str(paths.decompressed),
        "decompress",
        str(paths.baserom),
        implicit=["tools/rommy.py"],
        implicit_outputs=[str(paths.manifest)],
        variables={"manifest": str(paths.manifest)},
    )
    ninja.rule(
        "split",
        "$python -m splat split $in && touch $out",
        description="SPLIT $in",
        generator=True,
        # Skip rebuilding untouched .s/.bin files when splat re-runs.
        restat=True,
        pool="console",
    )
    ninja.build(
        paths.split_stamp,
        "split",
        str(paths.yaml),
        implicit=[*(str(p) for p in splat_deps(paths.yaml)), str(paths.decompressed)],
        implicit_outputs=[str(paths.ld_script), *(str(p) for p in paths.undefined_lds)],
    )
    ninja.newline()

    configure_args = shlex.join(sys.argv[1:])
    ninja.rule(
        "configure",
        f"$python configure.py {configure_args}".rstrip(),
        description="CONFIGURE",
        generator=True,
    )
    ninja.build(
        "build.ninja",
        "configure",
        implicit=[
            "configure.py",
            "tools/tools.toml",
            "tools/download_tool.py",
            paths.split_stamp,
        ],
    )
    ninja.newline()
    return tool_stamps


def emit_build(
    ninja,
    paths,
    overrides,
    tool_stamps,
    cross,
    ld_flags,
    *,
    host_cc,
    no_check,
    compressed,
):
    """Emit compilation, assembly, linking, ROM generation, and checksum rules."""
    ido = download_tool.tool_exe("ido", override=overrides.get("ido"))
    asm_processor = download_tool.tool_exe(
        "asm-processor", override=overrides.get("asm-processor")
    )
    # Only ido and asm-processor are needed to compile; other tools are fetched
    # on demand via `ninja tools`.
    compile_tools = [
        stamp
        for name, stamp in tool_stamps.items()
        if name in ("ido", "asm-processor")
    ]
    as_cmd = shlex.join([f"{cross}as", *ASFLAGS])
    ld_cmd = shlex.join([f"{cross}ld", *ld_flags])
    objcopy_cmd = shlex.quote(f"{cross}objcopy")

    check_arg = ""
    if not no_check:
        host_cc_parts = shlex.split(host_cc)
        if not host_cc_parts:
            sys.exit("configure: --host-cc must not be empty.")
        check_cmd = shlex.join([*host_cc_parts, *CHECK_FLAGS])
        check_arg = f" --check {shlex.quote(check_cmd)}"

    ninja.rule(
        "cc",
        f"$python tools/build/cc.py $in $out"
        f" --ido {shlex.quote(str(ido))}"
        f" --asm-processor {shlex.quote(str(asm_processor))}"
        f" --as {shlex.quote(as_cmd)}"
        f"{check_arg}"
        f" --encoding $encoding"
        f" -- {shlex.join(CFLAGS)} $optflags $isaflags",
        description="CC $in",
        depfile="$out.d",
        deps="gcc",
    )
    ninja.rule(
        "as",
        f"{as_cmd} --MD $out.d -o $out $in",
        description="AS $in",
        depfile="$out.d",
        deps="gcc",
    )
    ninja.rule(
        "as_encoded",
        f"$python tools/build/as.py $in $out --encoding $encoding"
        f" -- {as_cmd} --MD $out.d",
        description="AS $in",
        depfile="$out.d",
        deps="gcc",
    )
    ninja.rule(
        "bin",
        f"{ld_cmd} -r -b binary -o $out $in",
        description="BIN $in",
    )
    ninja.newline()

    objects = linker_objects(paths.ld_script, paths.build_dir)
    if not objects:
        sys.exit(f"configure: No objects were found in linker script {paths.ld_script}.")

    encoding_overrides = ENCODING_OVERRIDES.get(paths.version, {})
    c_units = []
    for obj, src in objects.items():
        if src.endswith(".c"):
            opt = OPTFLAGS_OVERRIDES.get(src, OPTFLAGS)
            isa = MIPSISA
            ninja.build(
                obj,
                "cc",
                src,
                implicit=["tools/build/cc.py"],
                # order_only ensures tools exist without forcing full rebuilds.
                order_only=compile_tools,
                variables={
                    "optflags": shlex.join(opt),
                    "isaflags": shlex.join(isa),
                    "encoding": encoding_overrides.get(src, ENCODING),
                },
            )
            c_units.append(src)
        elif src.endswith(".s"):
            src_path = ROOT / src
            data = src_path.read_bytes() if src_path.exists() else b""
            if data.isascii():
                ninja.build(obj, "as", src)
            else:
                # GNU as rejects raw Shift-JIS/EUC-JP bytes; transcode first.
                ninja.build(
                    obj,
                    "as_encoded",
                    src,
                    implicit=["tools/build/as.py"],
                    variables={"encoding": encoding_overrides.get(src, ENCODING)},
                )
        elif src.endswith(".bin"):
            ninja.build(obj, "bin", src)
        else:
            sys.exit(
                f"configure: No build rule is defined for {src} (linked as {obj})."
            )
    ninja.newline()

    elf = f"{paths.build_dir}/{BASENAME}.elf"
    rom = f"{paths.build_dir}/{BASENAME}.z64"
    ld_scripts = " ".join(
        f"-T {shlex.quote(str(p))}" for p in [paths.ld_script, *paths.undefined_lds]
    )
    ultralib_inputs = sorted(
        str(path)
        for root in ("src", "include")
        for path in (ROOT / ULTRALIB_DIR / root).rglob("*")
        if path.is_file()
    )
    ninja.rule(
        "ultralib",
        f"ln -sfn {shlex.quote(str(Path(ido).parent))} {ULTRALIB_DIR}/tools/ido"
        f" && make -C {ULTRALIB_DIR} VERSION=I TARGET=libultra_rom COMPARE=0"
        f" CROSS={shlex.quote(cross)} -j$$(nproc) > /dev/null",
        description="MAKE ultralib",
        restat=True,
    )
    ninja.build(
        ULTRALIB_ARCHIVE,
        "ultralib",
        ultralib_inputs,
        order_only=compile_tools,
    )
    ninja.rule(
        "lib_archive",
        f"$python tools/build/lib_archive.py $in $out --ld-script {shlex.quote(str(paths.ld_script))}"
        f" --ar {shlex.quote(f'{cross}ar')} --objcopy {shlex.quote(f'{cross}objcopy')}",
        description="AR $out",
    )
    ninja.build(
        LIBULTRA_ARCHIVE,
        "lib_archive",
        ULTRALIB_ARCHIVE,
        implicit=["tools/build/lib_archive.py", str(paths.ld_script)],
    )
    ninja.rule(
        "ld",
        f"{ld_cmd} {ld_scripts} -Map $map --no-check-sections --emit-relocs -o $out"
        f" $in --whole-archive {LIBULTRA_ARCHIVE} --no-whole-archive",
        description="LD $out",
    )
    ninja.build(
        elf,
        "ld",
        list(objects),
        implicit=[
            str(paths.ld_script),
            *(str(p) for p in paths.undefined_lds),
            LIBULTRA_ARCHIVE,
        ],
        implicit_outputs=[f"{paths.build_dir}/{BASENAME}.map"],
        variables={"map": f"{paths.build_dir}/{BASENAME}.map"},
    )
    ninja.rule(
        "objcopy",
        f"{objcopy_cmd} -O binary --pad-to=0x2000000 --gap-fill=0x00 $in $out",
        description="OBJCOPY $out",
    )
    ninja.rule(
        "sha1check",
        "$python tools/build/sha1check.py $in $out",
        description="SHA1 $in",
    )

    if compressed:
        uncompressed = f"{paths.build_dir}/{BASENAME}.uncompressed.z64"
        ninja.build(uncompressed, "objcopy", elf)
        ninja.rule(
            "compress",
            "$python tools/rommy.py compress --input $in --output $out"
            " --manifest $manifest --pad",
            description="COMPRESS $out",
        )
        ninja.build(
            rom,
            "compress",
            uncompressed,
            implicit=["tools/rommy.py", str(paths.manifest)],
            variables={"manifest": str(paths.manifest)},
        )
        sha1 = paths.config_dir / f"{BASENAME}.sha1"
    else:
        ninja.build(rom, "objcopy", elf)
        sha1 = paths.config_dir / f"{BASENAME}.uncompressed.sha1"

    ok = f"{paths.build_dir}/{BASENAME}.ok"
    # rom is implicit; sha1check.py reads the ROM path from the .sha1 file.
    ninja.build(ok, "sha1check", str(sha1), implicit=[rom, "tools/build/sha1check.py"])
    ninja.default(ok)
    return objects, c_units


def write_objdiff(c_units, build_dir):
    """Write objdiff.json for all compiled C translation units if changed."""
    units = []
    for src in sorted(c_units):
        name = src.removeprefix("src/").removesuffix(".c")
        units.append(
            {
                "name": name,
                "target_path": f"expected/targets/{name}.o",
                "base_path": f"{build_dir}/{src}.o",
                "metadata": {"source_path": src},
            }
        )
    config = {
        "$schema": "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json",
        "custom_make": "ninja",
        "build_target": False,
        "build_base": True,
        "watch_patterns": ["src/**/*.c", "src/**/*.h", "include/**/*.h"],
        "units": units,
    }
    text = json.dumps(config, indent=2) + "\n"
    out = ROOT / "objdiff.json"
    if not out.exists() or out.read_text() != text:
        out.write_text(text)


def main():
    """Generate build.ninja and objdiff.json for the selected ROM configuration."""
    args = parse_args()
    os.chdir(ROOT)

    paths = BuildPaths.for_version(args.version)
    cross = find_cross(args.cross)
    emu = (
        args.ld_emulation
        if args.ld_emulation is not None
        else detect_ld_emulation(cross)
    )
    ld_flags = ["-m", emu] if emu else []

    tools = download_tool.load_tools()
    overrides = parse_tool_overrides(args.tool, tools)

    buf = io.StringIO()
    ninja = ninja_syntax.Writer(buf, width=120)
    ninja.comment("Generated by configure.py; edit that instead.")
    ninja.variable("ninja_required_version", "1.10")
    ninja.variable("python", sys.executable)
    ninja.newline()

    tool_stamps = emit_bootstrap(ninja, paths, tools, overrides)

    if not paths.ld_script.exists():
        # Set default so pre-split `ninja` / `ninja -n` only rebuilds build.ninja.
        ninja.default("build.ninja")
        (ROOT / "build.ninja").write_text(buf.getvalue())
        print(
            f"configure: Wrote build.ninja. Run 'ninja' to split the ROM first "
            f"({paths.ld_script} does not exist yet)."
        )
        return

    objects, c_units = emit_build(
        ninja,
        paths,
        overrides,
        tool_stamps,
        cross,
        ld_flags,
        host_cc=args.host_cc,
        no_check=args.no_check,
        compressed=args.compressed,
    )

    (ROOT / "build.ninja").write_text(buf.getvalue())
    write_objdiff(c_units, paths.build_dir)
    count = len(objects)
    noun = "object" if count == 1 else "objects"
    print(f"configure: Wrote build.ninja ({count} {noun}) and objdiff.json.")


if __name__ == "__main__":
    main()