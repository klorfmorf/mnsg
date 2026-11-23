#!/usr/bin/env python3
"""Verify a file against a SHA-1 checksum file and touch a stamp on success."""

import argparse
import hashlib
import sys
from pathlib import Path


def parse_args():
    """Parse command-line options for verifying a SHA-1 checksum."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "sha1file",
        type=Path,
        help="Path to the SHA-1 checksum file.",
    )
    parser.add_argument(
        "stamp",
        type=Path,
        help="Path to the stamp file to touch when verification succeeds.",
    )
    parser.add_argument(
        "--file",
        dest="target",
        type=Path,
        help="Path to the file to verify (defaults to the path in SHA1FILE).",
    )
    return parser.parse_args()


def read_expected(sha1_path, target):
    """Read the expected SHA-1 digest and target path from sha1_path."""
    if not sha1_path.is_file():
        sys.exit(f"sha1check: Checksum file not found: {sha1_path}.")
    lines = [
        line.strip()
        for line in sha1_path.read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]
    if len(lines) != 1:
        sys.exit(
            f"sha1check: Expected exactly one entry in {sha1_path}, "
            f"found {len(lines)}."
        )

    parts = lines[0].split(maxsplit=1)
    expected = parts[0].lower()
    if len(expected) != 40 or not all(c in "0123456789abcdef" for c in expected):
        sys.exit(f"sha1check: Invalid SHA-1 digest {parts[0]!r} in {sha1_path}.")

    if target is None:
        if len(parts) < 2:
            sys.exit(
                f"sha1check: No target path was found in {sha1_path}; pass --file."
            )
        # Strip the leading '*' emitted by `sha1sum -b`.
        target = Path(parts[1].lstrip("*"))
    return expected, target


def file_sha1(path):
    """Compute the lowercase SHA-1 hex digest of path."""
    if not path.is_file():
        sys.exit(f"sha1check: Target file not found: {path}.")
    with path.open("rb") as f:
        return hashlib.file_digest(f, "sha1").hexdigest()


def main():
    """Verify the target file's SHA-1 digest and update the output stamp."""
    args = parse_args()
    args.stamp.unlink(missing_ok=True)

    expected, target = read_expected(args.sha1file, args.target)
    actual = file_sha1(target)
    if actual != expected:
        print(
            f"sha1check: Checksum mismatch for {target}.\n"
            f"  Expected: {expected}\n"
            f"  Actual:   {actual}",
            file=sys.stderr,
        )
        return 1

    print(f"sha1check: Verified {target} ({actual}).")
    args.stamp.parent.mkdir(parents=True, exist_ok=True)
    args.stamp.touch()
    return 0


if __name__ == "__main__":
    sys.exit(main())