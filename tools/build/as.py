#!/usr/bin/env python3
"""Transcode a UTF-8 assembly file and pipe it to the target assembler."""

import argparse
import subprocess
import sys
from pathlib import Path


def parse_args(argv):
    """Parse wrapper options and split out the underlying assembler command."""
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        "src",
        type=Path,
        help="Path to the UTF-8 assembly source file.",
    )
    parser.add_argument(
        "obj",
        type=Path,
        help="Path to the output object file.",
    )
    parser.add_argument(
        "--encoding",
        required=True,
        help="Target character encoding passed to the assembler.",
    )
    if "--" in argv:
        idx = argv.index("--")
        own_argv, as_argv = argv[:idx], argv[idx + 1 :]
    else:
        own_argv, as_argv = argv, []

    args = parser.parse_args(own_argv)
    if not as_argv:
        parser.error("Missing '--' followed by the assembler command.")
    return args, as_argv


def transcode(src_path, encoding):
    """Read a UTF-8 assembly file and encode its contents for the assembler."""
    if not src_path.is_file():
        sys.exit(f"as: Source file not found: {src_path}.")
    try:
        text = src_path.read_text(encoding="utf-8")
    except UnicodeDecodeError as err:
        sys.exit(f"as: Failed to decode {src_path} as UTF-8: {err}.")
    try:
        return text.encode(encoding)
    except (LookupError, UnicodeEncodeError) as err:
        sys.exit(f"as: Failed to encode {src_path} as {encoding}: {err}.")


def main():
    """Transcode the assembly source and run the assembler with input on stdin."""
    args, as_argv = parse_args(sys.argv[1:])
    payload = transcode(args.src, args.encoding)
    args.obj.parent.mkdir(parents=True, exist_ok=True)
    # GNU as reads the converted assembly from standard input.
    try:
        result = subprocess.run([*as_argv, "-o", str(args.obj)], check=False, input=payload)
    except OSError as err:
        sys.exit(f"as: Failed to launch assembler {as_argv[0]!r}: {err}.")
    return result.returncode


if __name__ == "__main__":
    sys.exit(main())