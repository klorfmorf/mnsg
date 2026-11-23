#!/usr/bin/env python3
"""Compile a C translation unit for the ROM build."""

import argparse
import re
import shlex
import subprocess
import sys
from pathlib import Path

GLOBAL_ASM_RE = re.compile(rb"^\s*#\s*pragma\s+GLOBAL_ASM\b", re.MULTILINE)


def parse_args(argv):
    """Parse compiler wrapper options and extract trailing IDO flags."""
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        "src",
        type=Path,
        help="Path to the UTF-8 C source file.",
    )
    parser.add_argument(
        "obj",
        type=Path,
        help="Path to the output object file.",
    )
    parser.add_argument(
        "--ido",
        required=True,
        help="Path to the IDO compiler executable.",
    )
    parser.add_argument(
        "--asm-processor",
        required=True,
        help="Path to the asm-processor executable.",
    )
    parser.add_argument(
        "--as",
        dest="assembler",
        required=True,
        help="Target assembler command line.",
    )
    parser.add_argument(
        "--check",
        help="Optional host C compiler command line for syntax checks and header deps.",
    )
    parser.add_argument(
        "--encoding",
        default="Shift_JIS",
        help="Target string encoding for IDO (default: Shift_JIS).",
    )
    if "--" in argv:
        idx = argv.index("--")
        own_argv, cflags = argv[:idx], argv[idx + 1 :]
    else:
        own_argv, cflags = argv, []

    args = parser.parse_args(own_argv)
    if not shlex.split(args.assembler):
        parser.error("--as must not be empty.")
    if args.check is not None and not shlex.split(args.check):
        parser.error("--check must not be empty when provided.")
    return args, cflags


def run(cmd):
    """Execute a subprocess command and exit with its status code on failure."""
    try:
        result = subprocess.run(cmd, check=False)
    except OSError as err:
        sys.exit(f"cc: Failed to execute {cmd[0]!r}: {err}.")
    if result.returncode:
        sys.exit(result.returncode)


def encode_c_source(src_path, raw_bytes, out_path, encoding):
    """Transcode a UTF-8 C source file into the target encoding at out_path."""
    try:
        text = raw_bytes.decode("utf-8")
    except UnicodeDecodeError as err:
        sys.exit(f"cc: Failed to decode {src_path} as UTF-8: {err}.")
    try:
        out_path.write_bytes(text.encode(encoding))
    except (LookupError, UnicodeEncodeError) as err:
        sys.exit(f"cc: Failed to encode {src_path} as {encoding}: {err}.")


def _depfile_inputs(path, obj):
    """Extract dependency paths for obj from a Makefile-style depfile."""
    text = re.sub(r"\\\r?\n", " ", path.read_text(encoding="utf-8"))
    inputs = []
    for line in text.splitlines():
        target, sep, rest = line.partition(":")
        if sep and target.strip() == str(obj):
            inputs.extend(rest.split())
    return inputs


def write_depfile(dep_path, obj, deps):
    """Write merged dependencies in Makefile format for Ninja's gcc depfile parser."""
    formatted = " \\\n  ".join(sorted(deps))
    content = f"{obj}: {formatted}\n" if formatted else f"{obj}:\n"
    dep_path.write_text(content, encoding="utf-8")


def main():
    """Run optional host checks, compile the C file, and emit its merged depfile."""
    args, cflags = parse_args(sys.argv[1:])
    if not args.src.is_file():
        sys.exit(f"cc: Source file not found: {args.src}.")

    obj = args.obj
    obj.parent.mkdir(parents=True, exist_ok=True)
    check_d = obj.with_name(f"{obj.name}.check.d")
    # asm-processor names its dependency file after the object, minus .o.
    asmproc_d = obj.with_suffix(".asmproc.d")
    encoded_c = obj.with_name(f"{obj.name}.encoded.c")

    try:
        check_d.unlink(missing_ok=True)
        asmproc_d.unlink(missing_ok=True)
        encoded_c.unlink(missing_ok=True)

        if args.check is not None:
            run(
                [
                    *shlex.split(args.check),
                    "-MMD",
                    "-MT",
                    str(obj),
                    "-MF",
                    str(check_d),
                    str(args.src),
                ]
            )

        source = args.src.read_bytes()
        if GLOBAL_ASM_RE.search(source):
            run(
                [
                    args.asm_processor,
                    "--input-enc=utf-8",
                    f"--output-enc={args.encoding}",
                    args.ido,
                    "--",
                    *shlex.split(args.assembler),
                    "--",
                    *cflags,
                    "-c",
                    "-o",
                    str(obj),
                    str(args.src),
                ]
            )
        else:
            # asm-processor compiles from a randomly named temp file that ends up
            # in .mdebug; invoke IDO directly when no GLOBAL_ASM is present so the
            # object stays reproducible.
            compile_src = str(args.src)
            if not source.isascii():
                encode_c_source(args.src, source, encoded_c, args.encoding)
                compile_src = str(encoded_c)
            run([args.ido, *cflags, "-c", "-o", str(obj), compile_src])

        deps = set()
        if check_d.exists():
            deps |= set(_depfile_inputs(check_d, obj))
        if asmproc_d.exists():
            deps |= set(_depfile_inputs(asmproc_d, obj))
        write_depfile(obj.with_name(f"{obj.name}.d"), obj, deps)
    finally:
        check_d.unlink(missing_ok=True)
        asmproc_d.unlink(missing_ok=True)
        encoded_c.unlink(missing_ok=True)


if __name__ == "__main__":
    main()