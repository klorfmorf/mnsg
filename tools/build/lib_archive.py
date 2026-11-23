#!/usr/bin/env python3
"""Repack the archive members used by a linker script into a smaller archive.

The linker script names archive members explicitly (`lib.a:member.o(.text)`),
but GNU ld only places members it has loaded. Linking the full library would
pull in members the ROM does not contain, placing them outside the layout
described by the script.
"""

import argparse
import re
import shlex
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

ELF_MAGIC = b"\x7fELF"
ELFCLASS32 = 1
ELFDATA2MSB = 2
EM_MIPS = 8
ELF32_E_FLAGS_OFFSET = 36
EF_MIPS_ABI_MASK = 0x0000F000
EF_MIPS_ABI_O32 = 0x00001000


def parse_args():
    """Parse command-line options for repacking a library archive."""
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument(
        "archive",
        type=Path,
        help="Path to the input archive to extract members from.",
    )
    parser.add_argument(
        "out",
        type=Path,
        help="Path to the repacked output archive.",
    )
    parser.add_argument(
        "--ld-script",
        type=Path,
        required=True,
        help="Path to the linker script referencing archive members.",
    )
    parser.add_argument(
        "--ar",
        required=True,
        help="Archiver command line.",
    )
    parser.add_argument(
        "--objcopy",
        required=True,
        help="Objcopy command line.",
    )
    args = parser.parse_args()
    if not shlex.split(args.ar):
        parser.error("--ar must not be empty.")
    if not shlex.split(args.objcopy):
        parser.error("--objcopy must not be empty.")
    return args


def find_used_members(ld_script, out_path):
    """Collect unique object member names referenced for out_path in link order."""
    if not ld_script.is_file():
        sys.exit(f"lib_archive: Linker script not found: {ld_script}.")
    pattern = re.compile(
        rf"(?<![^\s,(]){re.escape(out_path.as_posix())}:(\S+?\.o)\("
    )
    text = ld_script.read_text(encoding="utf-8")
    members = list(dict.fromkeys(pattern.findall(text)))
    if not members:
        sys.exit(
            f"lib_archive: Linker script {ld_script} does not reference {out_path}."
        )
    return members


def set_o32_abi(path):
    """Set EF_MIPS_ABI_O32 in the ELF32 big-endian MIPS header of path."""
    with path.open("r+b") as f:
        header = f.read(40)
        if len(header) < 40 or header[:4] != ELF_MAGIC:
            sys.exit(f"lib_archive: Invalid ELF header in {path}.")
        ei_class, ei_data = header[4], header[5]
        (machine,) = struct.unpack_from(">H", header, 18)
        if ei_class != ELFCLASS32 or ei_data != ELFDATA2MSB or machine != EM_MIPS:
            sys.exit(
                f"lib_archive: Expected a 32-bit big-endian MIPS ELF object at {path}."
            )
        (flags,) = struct.unpack_from(">I", header, ELF32_E_FLAGS_OFFSET)
        new_flags = (flags & ~EF_MIPS_ABI_MASK) | EF_MIPS_ABI_O32
        f.seek(ELF32_E_FLAGS_OFFSET)
        f.write(struct.pack(">I", new_flags))


def run(cmd, *, cwd):
    """Run a subprocess command in cwd and exit with its status code on failure."""
    try:
        result = subprocess.run(cmd, check=False, cwd=cwd)
    except OSError as err:
        sys.exit(f"lib_archive: Failed to execute {cmd[0]!r}: {err}.")
    if result.returncode:
        sys.exit(result.returncode)


def main():
    """Extract referenced archive members, normalize them for GNU ld, and repack."""
    args = parse_args()
    if not args.archive.is_file():
        sys.exit(f"lib_archive: Input archive not found: {args.archive}.")

    members = find_used_members(args.ld_script, args.out)
    ar = shlex.split(args.ar)
    objcopy = shlex.split(args.objcopy)
    archive_path = args.archive.resolve()

    args.out.parent.mkdir(parents=True, exist_ok=True)
    # Create the staging directory beside args.out so the final replace is atomic.
    with tempfile.TemporaryDirectory(
        prefix=f".{args.out.name}-", dir=args.out.parent
    ) as tmp:
        tmp_dir = Path(tmp)
        run([*ar, "x", str(archive_path), *members], cwd=tmp_dir)
        for member in members:
            member_path = tmp_dir / member
            if not member_path.is_file():
                sys.exit(
                    f"lib_archive: Member {member!r} was not extracted "
                    f"from {args.archive}."
                )
            # IDO's assembler leaves local symbols after global ones, which binutils
            # ld rejects; objcopy rewrites the symbol table in the order ld expects.
            run([*objcopy, member], cwd=tmp_dir)
            # objcopy drops the o32 ABI flag on -mips3 -32 objects (ll, llcvt, ...).
            set_o32_abi(member_path)

        staged_out = tmp_dir / ".output.a"
        run([*ar, "rcs", staged_out.name, *members], cwd=tmp_dir)
        staged_out.replace(args.out)


if __name__ == "__main__":
    main()