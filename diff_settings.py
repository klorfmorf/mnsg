#!/usr/bin/env python3

import argparse
from pathlib import Path

def add_custom_arguments(parser: argparse.ArgumentParser):
    version = "usa"

    make_options = Path(".make_options")
    if make_options.exists():
        with make_options.open() as f:
            for line in f:
                if "VERSION" in line and "=" in line:
                    version = line.split("=")[1].strip()

    parser.add_argument("-v", "--version", default=version)

def apply(config, args):
    version = args.version

    config["baseimg"] = f"expected/build/{version}/mnsg.z64"
    config["myimg"]   = f"build/{version}/mnsg.z64"
    config["mapfile"] = f"build/{version}/mnsg.map"
    config["source_directories"] = ["./src", "./include", "./asm", "./libultra"]
    config["objdump_flags"] = ["-Mreg-names=32"]
    config["makeflags"] = [f"VERSION={version}", "COMPRESSED=no", "PERMUTER=1"]