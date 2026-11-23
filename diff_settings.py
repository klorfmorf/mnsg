#!/usr/bin/env python3
# asm-differ settings: `uv run build/tools/asm-differ-*/diff.py -mwo FUNC`.

import argparse
import shutil


def add_custom_arguments(parser: argparse.ArgumentParser):
    parser.add_argument("-v", "--version", default="usa")


def apply(config, args):
    version = args.version

    config["baseimg"] = f"expected/build/{version}/mnsg.z64"
    config["myimg"] = f"build/{version}/mnsg.z64"
    config["mapfile"] = f"build/{version}/mnsg.map"
    config["source_directories"] = ["./src", "./include", "./asm", "./libultra"]
    config["objdump_flags"] = ["-Mreg-names=32"]
    # The prefixes configure.py looks for; asm-differ's own list lacks mips64-linux-gnu-.
    for prefix in ("mips-linux-gnu-", "mips64-linux-gnu-", "mips64-elf-"):
        if shutil.which(prefix + "objdump"):
            config["objdump_executable"] = prefix + "objdump"
            break
    config["make_command"] = ["ninja"]
