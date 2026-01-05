#!/usr/bin/env python3
"""
Rommy - A tool for compressing and decompressing Nintendo 64 game ROMs.

This tool handles ROMs that use the Nisitenma-Ichigo file table format, commonly
found in Konami N64 games. The file table contains ROM addresses to various 
compressed assets (code, textures, graphics, object placements, scenario code, 
etc.) within the ROM.

File Table Format
-----------------
The file table is identified by the ASCII signature "Nisitenma-Ichigo" (16 bytes).
Immediately following this signature are the file table entries with no padding.

Each entry is a 32-bit big-endian value:
    +---+-------------------------------+
    |31 | 30                          0 |
    +---+-------------------------------+
    | C |        ROM Offset             |
    +---+-------------------------------+

    - Bits 0-30 (31 bits): ROM offset/address of the file
    - Bit 31 (high bit): Compression flag (C)
      - 1 = File is compressed with LZKN64 compression
      - 0 = File is raw/uncompressed data (may use different compression)

Files are stored sequentially in the ROM with no gaps between them. The end
address of file N is determined by the start address of file N+1. The table
is terminated by a zero entry (0x00000000).

Manifest Format
---------------
The manifest (YAML) preserves metadata from decompression for later recompression:

    version: 1
    file_table_address: "0x12340"  # For verification only, not used for lookup
    files:
      - index: 0
        compressed: true
        original_offset: "0x1000"
        original_size: 4096
        decompressed_size: 5632
        decompressed_crc32: "0xABCD1234"

This enables:
- Round-trip compression using original compression decisions
- Verification that modified files match expected sizes/checksums
- Detection of file table shifts or corruption (with --verify)
- Efficiency comparison (new compressed size vs original)

Note: The file table is ALWAYS located by searching for the Nisitenma-Ichigo
signature, not by using the manifest address. This ensures the tool works
correctly even when ROM structure shifts due to code modifications.

Usage Examples
--------------
    # Decompress a ROM (auto-detects file table location)
    python rommy.py decompress -i input.z64 -o output.z64 -m manifest.yaml

    # Compress a ROM using manifest (with verification)
    python rommy.py compress -i input.z64 -o output.z64 -m manifest.yaml --verify

    # Override file table location if auto-detection fails
    python rommy.py decompress -i input.z64 -o output.z64 -a 0x1234

Dependencies
------------
- lzkn64: LZKN64 compression library ('pip install lzkn64' or 'uv add lzkn64')
- PyYAML: YAML parsing library ('pip install pyyaml' or 'uv add pyyaml')

N64 Header CRCs
---------------
By default, Rommy recalculates the two CRC32 checksums in the N64 ROM header
(offsets 0x10 and 0x14). These checksums are verified by the N64 IPL during
boot. The calculation is CIC-chip dependent; the CIC type is auto-detected
from the bootcode region (0x40-0x1000).

Supported CIC variants: 6101, 6102, 6103, 6105, 6106.
Unknown bootcodes default to CIC-6105 behavior.

Use --no-fix-crcs to skip this step if needed.
"""

from __future__ import annotations

import argparse
import struct
import sys
import time
import zlib
from dataclasses import dataclass, field
from enum import Enum
from pathlib import Path
from typing import Any, Generator

import yaml

try:
    import lzkn64
except ImportError:
    print(
        "Error: lzkn64 module not found. "
        "Please install it (e.g., 'pip install lzkn64' or 'uv add lzkn64').",
        file=sys.stderr,
    )
    sys.exit(1)


# =============================================================================
# Constants
# =============================================================================

# The magic signature identifying the start of the Nisitenma-Ichigo file table.
# This 16-byte ASCII string precedes the file table entries in all Konami N64
# games using this compression scheme.
NISITENMA_SIGNATURE = b"Nisitenma-Ichigo"
SIGNATURE_LENGTH = len(NISITENMA_SIGNATURE)

# Bit masks for parsing file table entries (32-bit big-endian values)
OFFSET_MASK = 0x7FFFFFFF  # Lower 31 bits: ROM offset
COMPRESSED_FLAG = 0x80000000  # Bit 31: Compression indicator

# Size of each file table entry in bytes
ENTRY_SIZE_BYTES = 4

# N64 alignment requirement for compressed data
N64_ALIGNMENT = 2

# Current manifest format version
MANIFEST_VERSION = 1

# =============================================================================
# N64 ROM Header Constants
# =============================================================================

# ROM header layout
N64_HEADER_SIZE = 0x40
N64_BOOTCODE_SIZE = 0x1000 - N64_HEADER_SIZE  # 0xFC0 bytes
N64_CRC1_OFFSET = 0x10
N64_CRC2_OFFSET = 0x14

# Checksum calculation region
N64_CHECKSUM_START = 0x1000
N64_CHECKSUM_LENGTH = 0x100000  # 1 MB

# CIC chip identification via bootcode CRC32
# Maps bootcode CRC -> (CIC type, seed value)
CIC_VARIANTS = {
    0x6170A4A1: (6101, 0xF8CA4DDC),
    0x90BB6CB5: (6102, 0xF8CA4DDC),
    0x0B050EE0: (6103, 0xA3886759),
    0x98BC2C86: (6105, 0xDF26F436),
    0xACC8580A: (6106, 0x1FEA617A),
}

# Default to CIC-6105 for unknown bootcodes
DEFAULT_CIC = (6105, 0xDF26F436)

# =============================================================================
# Exceptions
# =============================================================================


class RommyError(Exception):
    """Base exception for all Rommy-related errors."""

    pass


class FileTableNotFoundError(RommyError):
    """Raised when the Nisitenma-Ichigo file table cannot be located in the ROM."""

    pass


class FileTableError(RommyError):
    """Raised when the file table is invalid or corrupted."""

    pass


class CompressionError(RommyError):
    """Raised when compression or decompression fails."""

    pass


class ManifestError(RommyError):
    """Raised when manifest reading or writing fails."""

    pass


# =============================================================================
# Utility Functions
# =============================================================================


def read_u32_be(buffer: bytes, offset: int) -> int:
    """
    Reads a big-endian unsigned 32-bit integer from the buffer.

    Args:
        buffer: The byte buffer to read from.
        offset: The byte offset to start reading at.

    Returns:
        The 32-bit unsigned integer value.
    """
    return struct.unpack_from(">I", buffer, offset)[0]


def write_u32_be(buffer: bytearray, offset: int, value: int) -> None:
    """
    Writes a big-endian unsigned 32-bit integer to the buffer.

    Args:
        buffer: The mutable byte buffer to write to.
        offset: The byte offset to start writing at.
        value: The 32-bit unsigned integer value to write.
    """
    struct.pack_into(">I", buffer, offset, value)


def round_up_to_power_of_two(n: int) -> int:
    """
    Rounds a number up to the nearest power of two.

    Uses bit manipulation for efficiency. Handles edge cases:
    - Returns 0 for input 0
    - Returns 1 for input 1

    Args:
        n: The number to round up (must be non-negative).

    Returns:
        The smallest power of two greater than or equal to n.
    """
    if n <= 1:
        return n
    n -= 1
    n |= n >> 1
    n |= n >> 2
    n |= n >> 4
    n |= n >> 8
    n |= n >> 16
    return n + 1


def align_to_boundary(data: bytes, alignment: int) -> bytes:
    """
    Pads data with null bytes to meet the specified alignment boundary.

    Args:
        data: The data to align.
        alignment: The alignment boundary in bytes.

    Returns:
        The data padded to the alignment boundary.
    """
    remainder = len(data) % alignment
    if remainder == 0:
        return data
    padding_needed = alignment - remainder
    return data + (b"\x00" * padding_needed)


def calculate_crc32(data: bytes) -> int:
    """
    Calculates the CRC32 checksum of the given data.

    Args:
        data: The bytes to checksum.

    Returns:
        The unsigned 32-bit CRC32 value.
    """
    # zlib.crc32 returns a signed int on some platforms; mask to unsigned
    return zlib.crc32(data) & 0xFFFFFFFF


def find_nisitenma_signature(data: bytes) -> int:
    """
    Searches for the Nisitenma-Ichigo signature in ROM data.

    The signature marks the beginning of the file table. The actual
    file table entries begin immediately after the signature.

    Args:
        data: The ROM data to search through.

    Returns:
        The byte offset where the signature was found.

    Raises:
        FileTableNotFoundError: If the signature is not found.
    """
    index = data.find(NISITENMA_SIGNATURE)
    if index == -1:
        raise FileTableNotFoundError(
            "Nisitenma-Ichigo signature not found in ROM. "
            "This ROM may not use the expected file table format, "
            "or you may need to specify the address manually with -a."
        )
    return index


def parse_hex_or_int(value: int | str) -> int:
    """
    Parses a value that may be an integer or a hex string.

    Args:
        value: An integer, or a string like "0x1234" or "1234".

    Returns:
        The parsed integer value.
    """
    if isinstance(value, str):
        return int(value, 0)
    return value


def format_hex(value: int) -> str:
    """
    Formats an integer as a hexadecimal string with 0x prefix.

    Args:
        value: The integer to format.

    Returns:
        String like "0x1234".
    """
    return f"0x{value:X}"


def format_hex_padded(value: int, width: int = 8) -> str:
    """
    Formats an integer as a zero-padded hexadecimal string.

    Args:
        value: The integer to format.
        width: Minimum width (default 8 for 32-bit values).

    Returns:
        String like "0x0000ABCD".
    """
    return f"0x{value:0{width}X}"


# =============================================================================
# N64 ROM Header CRC Calculation
# =============================================================================


def rotate_left_32(value: int, shift: int) -> int:
    """
    Rotates a 32-bit value left by the specified number of bits.

    Args:
        value: The 32-bit value to rotate.
        shift: Number of bits to rotate (masked to 0-31).

    Returns:
        The rotated 32-bit value.
    """
    shift &= 31
    if shift == 0:
        return value & 0xFFFFFFFF
    return ((value << shift) | (value >> (32 - shift))) & 0xFFFFFFFF


def detect_n64_cic(data: bytes) -> tuple[int, int]:
    """
    Detects the CIC chip type used by the ROM based on bootcode CRC.

    The CIC (Checking Integrated Circuit) is a lockout chip in N64
    cartridges. Different CIC variants require different seed values
    for the header checksum calculation.

    Args:
        data: ROM data (must be at least 0x1000 bytes).

    Returns:
        Tuple of (cic_type, seed) where cic_type is 6101-6106.
        Defaults to CIC-6105 if bootcode is unrecognized.
    """
    bootcode = data[N64_HEADER_SIZE : N64_HEADER_SIZE + N64_BOOTCODE_SIZE]
    bootcode_crc = calculate_crc32(bootcode)

    return CIC_VARIANTS.get(bootcode_crc, DEFAULT_CIC)


def calculate_n64_header_crcs(data: bytes) -> tuple[int, int]:
    """
    Calculates the N64 ROM header CRC values.

    This implements the checksum algorithm used by the N64 IPL (Initial
    Program Loader) to verify ROM integrity. The algorithm is based on
    code by Andreas Sterbenz (uCON64) and Parasyte (snesrc).

    The checksum covers 1MB of ROM data starting at offset 0x1000.
    The specific calculation varies slightly based on the CIC chip type.

    Args:
        data: ROM data (must be at least 0x101000 bytes).

    Returns:
        Tuple of (crc1, crc2) values for header offsets 0x10 and 0x14.

    Raises:
        RommyError: If ROM is too small for CRC calculation.
    """
    required_size = N64_CHECKSUM_START + N64_CHECKSUM_LENGTH
    if len(data) < required_size:
        raise RommyError(
            f"ROM too small for N64 CRC calculation. "
            f"Need {required_size:,} bytes, got {len(data):,}."
        )

    cic_type, seed = detect_n64_cic(data)

    # Initialize registers with seed value
    t1 = t2 = t3 = t4 = t5 = t6 = seed

    # Process checksum region in 32-bit words
    for i in range(N64_CHECKSUM_START, N64_CHECKSUM_START + N64_CHECKSUM_LENGTH, 4):
        d = read_u32_be(data, i)

        # Detect 32-bit unsigned overflow
        if (t6 + d) > 0xFFFFFFFF:
            t4 = (t4 + 1) & 0xFFFFFFFF

        t6 = (t6 + d) & 0xFFFFFFFF
        t3 ^= d

        r = rotate_left_32(d, d & 0x1F)
        t5 = (t5 + r) & 0xFFFFFFFF

        if t2 > d:
            t2 ^= r
        else:
            t2 ^= t6 ^ d

        # CIC-6105 uses additional data from bootcode region
        if cic_type == 6105:
            bootcode_offset = N64_HEADER_SIZE + 0x0710 + (i & 0xFF)
            t1 = (t1 + (read_u32_be(data, bootcode_offset) ^ d)) & 0xFFFFFFFF
        else:
            t1 = (t1 + (t5 ^ d)) & 0xFFFFFFFF

    # Final CRC calculation varies by CIC type
    if cic_type == 6103:
        crc1 = ((t6 ^ t4) + t3) & 0xFFFFFFFF
        crc2 = ((t5 ^ t2) + t1) & 0xFFFFFFFF
    elif cic_type == 6106:
        crc1 = ((t6 * t4) + t3) & 0xFFFFFFFF
        crc2 = ((t5 * t2) + t1) & 0xFFFFFFFF
    else:
        # CIC-6101, 6102, 6105
        crc1 = (t6 ^ t4 ^ t3) & 0xFFFFFFFF
        crc2 = (t5 ^ t2 ^ t1) & 0xFFFFFFFF

    return crc1, crc2


def update_n64_header_crcs(data: bytearray, verbose: bool = False) -> tuple[int, int]:
    """
    Calculates and writes the N64 ROM header CRCs in place.

    Args:
        data: Mutable ROM data buffer.
        verbose: If True, logs the CIC type and CRC values.

    Returns:
        Tuple of (crc1, crc2) that were written.
    """
    cic_type, _ = detect_n64_cic(data)
    crc1, crc2 = calculate_n64_header_crcs(data)

    old_crc1 = read_u32_be(data, N64_CRC1_OFFSET)
    old_crc2 = read_u32_be(data, N64_CRC2_OFFSET)

    write_u32_be(data, N64_CRC1_OFFSET, crc1)
    write_u32_be(data, N64_CRC2_OFFSET, crc2)

    if verbose:
        if old_crc1 != crc1 or old_crc2 != crc2:
            print(
                f"Updated N64 header CRCs (CIC-{cic_type}): "
                f"{format_hex_padded(crc1)}, {format_hex_padded(crc2)}"
            )
        else:
            print(
                f"N64 header CRCs already correct (CIC-{cic_type}): "
                f"{format_hex_padded(crc1)}, {format_hex_padded(crc2)}"
            )

    return crc1, crc2


# =============================================================================
# Data Classes
# =============================================================================


@dataclass
class FileTableEntry:
    """
    Represents a single entry in the Nisitenma-Ichigo file table.

    Each entry encodes a file's ROM offset and compression status in a
    single 32-bit value.

    Attributes:
        offset: The ROM offset of the file (31-bit value, max ~2GB).
        is_compressed: Whether the file uses LZKN64 compression.
    """

    offset: int
    is_compressed: bool

    @classmethod
    def from_raw(cls, raw_value: int) -> FileTableEntry:
        """
        Creates a FileTableEntry from a raw 32-bit file table value.

        Args:
            raw_value: The raw 32-bit big-endian value from the file table.

        Returns:
            A FileTableEntry with parsed offset and compression flag.
        """
        return cls(
            offset=raw_value & OFFSET_MASK,
            is_compressed=bool(raw_value & COMPRESSED_FLAG),
        )

    def to_raw(self) -> int:
        """
        Converts the entry back to its raw 32-bit representation.

        Returns:
            The 32-bit value suitable for writing to the file table.
        """
        value = self.offset & OFFSET_MASK
        if self.is_compressed:
            value |= COMPRESSED_FLAG
        return value

    @property
    def is_terminator(self) -> bool:
        """Returns True if this entry is the zero terminator."""
        return self.offset == 0 and not self.is_compressed

    def __repr__(self) -> str:
        status = "compressed" if self.is_compressed else "raw"
        return f"FileTableEntry(0x{self.offset:08X}, {status})"


@dataclass
class FileInfo:
    """
    Contains information about a single file extracted from the file table.

    Attributes:
        index: Zero-based index of the file in the table.
        data: The raw file data from the ROM.
        entry: The original file table entry for this file.
    """

    index: int
    data: bytes
    entry: FileTableEntry

    @property
    def is_empty(self) -> bool:
        """Returns True if this file contains no data."""
        return len(self.data) == 0


@dataclass
class FileManifestEntry:
    """
    Manifest entry containing metadata about a single file.

    This information is recorded during decompression and used during
    recompression to restore original compression decisions and verify
    file integrity.

    Attributes:
        index: Zero-based index in the file table.
        compressed: Whether the file was compressed in the original ROM.
        original_offset: ROM offset in the original compressed ROM.
        original_size: Size in bytes in the original ROM (compressed if applicable).
        decompressed_size: Size in bytes after decompression.
        decompressed_crc32: CRC32 checksum of the decompressed data.
    """

    index: int
    compressed: bool
    original_offset: int
    original_size: int
    decompressed_size: int
    decompressed_crc32: int

    def to_dict(self) -> dict[str, Any]:
        """
        Converts to a dictionary for YAML serialization.

        Offsets and CRC32 are formatted as hex strings for readability.
        """
        return {
            "index": self.index,
            "compressed": self.compressed,
            "original_offset": format_hex(self.original_offset),
            "original_size": self.original_size,
            "decompressed_size": self.decompressed_size,
            "decompressed_crc32": format_hex_padded(self.decompressed_crc32),
        }

    @classmethod
    def from_dict(cls, data: dict[str, Any]) -> FileManifestEntry:
        """
        Creates a FileManifestEntry from a dictionary.

        Handles both integer and hex string formats for offsets/CRC32.
        """
        return cls(
            index=data["index"],
            compressed=data["compressed"],
            original_offset=parse_hex_or_int(data["original_offset"]),
            original_size=data["original_size"],
            decompressed_size=data["decompressed_size"],
            decompressed_crc32=parse_hex_or_int(data["decompressed_crc32"]),
        )

    def matches_data(self, data: bytes) -> tuple[bool, list[str]]:
        """
        Checks if the given data matches this manifest entry.

        Args:
            data: The file data to verify.

        Returns:
            Tuple of (matches: bool, discrepancies: list[str]).
        """
        issues: list[str] = []

        if len(data) != self.decompressed_size:
            issues.append(
                f"size mismatch (expected {self.decompressed_size}, "
                f"got {len(data)})"
            )

        actual_crc = calculate_crc32(data)
        if actual_crc != self.decompressed_crc32:
            issues.append(
                f"CRC32 mismatch (expected {format_hex_padded(self.decompressed_crc32)}, "
                f"got {format_hex_padded(actual_crc)})"
            )

        return len(issues) == 0, issues


class VerificationResult(Enum):
    """Result of file verification against manifest."""

    MATCH = "match"
    MODIFIED = "modified"
    MISSING_ENTRY = "missing_entry"


@dataclass
class CompressionStats:
    """
    Statistics collected during compression for reporting.

    Attributes:
        files_compressed: Number of files that were compressed.
        files_copied: Number of files copied without compression.
        files_modified: Number of files that differed from manifest.
        total_original_size: Sum of original compressed sizes from manifest.
        total_new_size: Sum of new compressed sizes.
        size_warnings: List of files where new size exceeds original.
    """

    files_compressed: int = 0
    files_copied: int = 0
    files_modified: int = 0
    total_original_size: int = 0
    total_new_size: int = 0
    size_warnings: list[str] = field(default_factory=list)

    def add_compressed(
        self, index: int, original_size: int, new_size: int
    ) -> None:
        """Records a compressed file and checks for size regression."""
        self.files_compressed += 1
        self.total_original_size += original_size
        self.total_new_size += new_size

        if new_size > original_size:
            overhead = new_size - original_size
            percent = (overhead / original_size) * 100 if original_size > 0 else 0
            self.size_warnings.append(
                f"File {index}: new size ({new_size}) exceeds original "
                f"({original_size}) by {overhead} bytes ({percent:.1f}%)"
            )

    def add_copied(self, size: int) -> None:
        """Records a file that was copied without compression."""
        self.files_copied += 1
        self.total_original_size += size
        self.total_new_size += size

    def report(self, verbose: bool = False) -> None:
        """Prints a summary of compression statistics."""
        print(f"\nCompression Statistics:")
        print(f"  Files compressed: {self.files_compressed}")
        print(f"  Files copied:     {self.files_copied}")
        if self.files_modified > 0:
            print(f"  Files modified:   {self.files_modified}")

        if self.total_original_size > 0:
            ratio = self.total_new_size / self.total_original_size
            delta = self.total_new_size - self.total_original_size
            sign = "+" if delta >= 0 else ""
            print(
                f"  Total data size:  {self.total_new_size:,} bytes "
                f"({sign}{delta:,}, {ratio:.2%} of original)"
            )

        if self.size_warnings:
            print(f"\nSize Regression Warnings ({len(self.size_warnings)}):")
            for warning in self.size_warnings[:10]:  # Limit output
                print(f"  - {warning}")
            if len(self.size_warnings) > 10:
                print(f"  ... and {len(self.size_warnings) - 10} more")


# =============================================================================
# Configuration
# =============================================================================


@dataclass
class RommyConfig:
    """
    Configuration container for Rommy operations.

    This class encapsulates all configuration options, decoupling the main
    logic from argparse and making the code easier to test and reuse.

    Attributes:
        input_path: Path to the input ROM file.
        output_path: Path to the output ROM file.
        command: The operation to perform ('compress' or 'decompress').
        manifest_path: Optional path to the manifest YAML file.
        file_table_address: Optional explicit address of the file table entries.
        pad_output: Whether to pad output to the nearest power of two.
        verbose: Whether to enable verbose logging.
        verify: Whether to verify files against manifest during compression.
        fix_crcs: Whether to recalculate N64 header CRCs.
    """

    input_path: Path
    output_path: Path
    command: str
    manifest_path: Path | None = None
    file_table_address: int | None = None
    pad_output: bool = False
    verbose: bool = False
    verify: bool = False
    fix_crcs: bool = True

    @classmethod
    def from_args(cls, args: argparse.Namespace) -> RommyConfig:
        """
        Creates a RommyConfig from parsed command-line arguments.

        Args:
            args: Parsed argparse namespace.

        Returns:
            A configured RommyConfig instance.
        """
        return cls(
            input_path=Path(args.input),
            output_path=Path(args.output),
            command=args.command,
            manifest_path=Path(args.manifest) if args.manifest else None,
            file_table_address=args.address,
            pad_output=args.pad,
            verbose=args.verbose,
            verify=getattr(args, "verify", False),
            fix_crcs=getattr(args, "fix_crcs", True),
        )


# =============================================================================
# Progress Display
# =============================================================================


class ProgressBar:
    """
    A simple console progress bar for tracking operation progress.

    When verbose mode is enabled, the progress bar is not displayed
    (detailed per-file logging is shown instead).

    Attributes:
        total: Total number of items to process.
        width: Width of the progress bar in characters.
        verbose: If True, progress bar is suppressed.
    """

    def __init__(self, total: int, width: int = 50, verbose: bool = False):
        self.total = total
        self.width = width
        self.verbose = verbose
        self._current = 0
        self._start_time = time.time()

    def update(self, step: int = 1) -> None:
        """Advances the progress bar by the given step amount."""
        self._current += step
        if not self.verbose:
            self._render()

    def _render(self) -> None:
        """Renders the current progress bar state to stdout."""
        if self.total == 0:
            return

        percent = self._current / self.total
        filled_length = int(self.width * percent)
        bar = "█" * filled_length + "-" * (self.width - filled_length)
        elapsed = time.time() - self._start_time

        sys.stdout.write(
            f"\rProgress: |{bar}| {percent:.1%} "
            f"({self._current}/{self.total}) - {elapsed:.2f}s"
        )
        sys.stdout.flush()

    def finish(self) -> None:
        """Completes the progress bar and moves to a new line."""
        if not self.verbose:
            sys.stdout.write("\n")
            sys.stdout.flush()


# =============================================================================
# Manifest Handling
# =============================================================================


class Manifest:
    """
    Handles reading and writing manifest files.

    The manifest stores metadata about files in the ROM, tracking which files
    should be compressed and their original characteristics. This enables
    round-trip compression/decompression and integrity verification.

    Note: The file_table_address stored in the manifest is used ONLY for
    verification (with --verify flag), not for locating the file table.
    The signature search is always performed, as ROM structure may shift
    during modding.

    Manifest Format (YAML):
        version: 1
        file_table_address: "0x12340"  # For verification only
        files:
          - index: 0
            compressed: true
            original_offset: "0x1000"
            original_size: 4096
            decompressed_size: 5632
            decompressed_crc32: "0xABCD1234"
          - index: 1
            compressed: false
            ...
    """

    def __init__(self, path: Path | None = None):
        """
        Initializes the Manifest handler.

        Args:
            path: Path to the manifest file, or None if no manifest is used.
        """
        self.path = path
        self._raw_data: dict[str, Any] | None = None
        self._entries: list[FileManifestEntry] | None = None
        self._loaded = False

    def _ensure_loaded(self) -> None:
        """Loads manifest data if not already loaded."""
        if self._loaded:
            return

        self._loaded = True
        self._raw_data = {}
        self._entries = []

        if not self.path or not self.path.exists():
            return

        try:
            with self.path.open("r", encoding="utf-8") as f:
                data = yaml.safe_load(f)

            if not isinstance(data, dict):
                raise ManifestError("Manifest root must be a dictionary")

            self._raw_data = data
            version = data.get("version", 0)

            if version != MANIFEST_VERSION:
                raise ManifestError(
                    f"Unsupported manifest version {version}. "
                    f"Expected version {MANIFEST_VERSION}."
                )

            files_data = data.get("files", [])
            if not isinstance(files_data, list):
                raise ManifestError("Manifest 'files' must be a list")

            self._entries = [
                FileManifestEntry.from_dict(entry) for entry in files_data
            ]

        except yaml.YAMLError as e:
            raise ManifestError(f"Failed to parse manifest YAML: {e}") from e
        except OSError as e:
            raise ManifestError(f"Failed to read manifest file: {e}") from e
        except KeyError as e:
            raise ManifestError(f"Manifest missing required field: {e}") from e

    @property
    def file_table_address(self) -> int | None:
        """
        Returns the file table address from the manifest.

        Returns:
            The file table offset, or None if not present.
        """
        self._ensure_loaded()
        if not self._raw_data:
            return None

        addr = self._raw_data.get("file_table_address")
        if addr is None:
            return None

        return parse_hex_or_int(addr)

    @property
    def entries(self) -> list[FileManifestEntry]:
        """
        Returns all file manifest entries.

        Returns:
            List of FileManifestEntry objects.
        """
        self._ensure_loaded()
        return self._entries or []

    def get_entry(self, index: int) -> FileManifestEntry | None:
        """
        Returns the manifest entry for a specific file index.

        Args:
            index: The zero-based file index.

        Returns:
            The FileManifestEntry, or None if not found.
        """
        self._ensure_loaded()
        if self._entries is None:
            return None

        for entry in self._entries:
            if entry.index == index:
                return entry
        return None

    @property
    def file_count(self) -> int:
        """Returns the number of file entries in the manifest."""
        self._ensure_loaded()
        return len(self._entries) if self._entries else 0

    def save(
        self,
        file_table_address: int,
        entries: list[FileManifestEntry],
        verbose: bool = False,
    ) -> None:
        """
        Saves manifest data to disk.

        Args:
            file_table_address: The offset of file table entries in the ROM.
            entries: List of file manifest entries.
            verbose: Whether to log the save operation.

        Raises:
            ManifestError: If the manifest file cannot be written.
        """
        if not self.path:
            return

        manifest_data = {
            "version": MANIFEST_VERSION,
            "file_table_address": format_hex(file_table_address),
            "files": [entry.to_dict() for entry in entries],
        }

        try:
            if verbose:
                print(f"Writing manifest to: {self.path}")

            self.path.parent.mkdir(parents=True, exist_ok=True)

            with self.path.open("w", encoding="utf-8") as f:
                yaml.dump(manifest_data, f, sort_keys=False, allow_unicode=True)

            # Update cache
            self._raw_data = manifest_data
            self._entries = entries
            self._loaded = True

        except OSError as e:
            raise ManifestError(f"Failed to write manifest file: {e}") from e


# =============================================================================
# Main ROM Handler
# =============================================================================


class Rommy:
    """
    Main class for ROM compression and decompression operations.

    This class handles loading ROMs, locating and parsing the Nisitenma-Ichigo
    file table, and performing compression or decompression of embedded files.

    The file table is automatically located by searching for the signature,
    but can be overridden via configuration if needed.

    Attributes:
        config: Configuration options for the operation.
        manifest: Manifest handler for reading/writing metadata.
    """

    def __init__(self, config: RommyConfig):
        """
        Initializes the Rommy processor.

        Args:
            config: Configuration specifying input/output paths and options.
        """
        self.config = config
        self.manifest = Manifest(config.manifest_path)

        # Internal state
        self._input_data: bytearray = bytearray()
        self._output_data: bytearray = bytearray()
        self._file_table_offset: int = 0
        self._file_table_entries: list[FileTableEntry] = []
        self._output_entries: list[int] = []

    def log(self, message: str) -> None:
        """Prints a message if verbose mode is enabled."""
        if self.config.verbose:
            print(message)

    def run(self) -> None:
        """
        Executes the main compression or decompression operation.

        Raises:
            RommyError: If any error occurs during processing.
        """
        operation = (
            "Compressing" if self.config.command == "compress" else "Decompressing"
        )
        print(f"Rommy - {operation} ROM...")

        self._load_input()
        self._locate_file_table()
        self._parse_file_table()
        self._validate_file_table()
        self._initialize_output()

        if self.config.command == "compress":
            self._process_compression()
        else:
            self._process_decompression()

        self._write_file_table_to_output()

        if self.config.pad_output:
            self._apply_power_of_two_padding()

        if self.config.fix_crcs:
            self._update_header_crcs()

        self._write_output()
        print("Done!")

    def _load_input(self) -> None:
        """Loads the input ROM file into memory."""
        self.log(f"Loading input ROM from: {self.config.input_path}")

        if not self.config.input_path.exists():
            raise RommyError(f"Input file not found: {self.config.input_path}")

        try:
            with self.config.input_path.open("rb") as f:
                self._input_data = bytearray(f.read())
        except OSError as e:
            raise RommyError(f"Failed to read input file: {e}") from e

        self.log(f"Loaded {len(self._input_data):,} bytes.")

    def _locate_file_table(self) -> None:
        """
        Locates the file table in the ROM.

        Resolution order:
        1. Explicit address from command-line argument (-a/--address)
        2. Auto-detection via Nisitenma-Ichigo signature search

        The manifest's file_table_address is NOT used for lookup (as ROM
        structure may shift during modding). It is only used for verification
        when --verify is passed.
        """
        # Priority 1: Explicit address from command line (user override)
        if self.config.file_table_address is not None:
            self._file_table_offset = self.config.file_table_address
            self.log(
                f"Using provided file table address: "
                f"{format_hex(self._file_table_offset)}"
            )
            return

        # Auto-detect via signature search
        self.log("Searching for Nisitenma-Ichigo signature...")
        signature_offset = find_nisitenma_signature(self._input_data)

        # File table entries start immediately after the 16-byte signature
        self._file_table_offset = signature_offset + SIGNATURE_LENGTH
        self.log(
            f"Found signature at {format_hex(signature_offset)}, "
            f"file table entries at {format_hex(self._file_table_offset)}"
        )

        # Verify against manifest if requested
        if self.config.verify:
            self._verify_file_table_address()

    def _verify_file_table_address(self) -> None:
        """
        Verifies the detected file table address against the manifest.

        Warns if the addresses don't match, which may indicate the ROM
        structure has shifted (e.g., due to code modifications).
        """
        manifest_offset = self.manifest.file_table_address
        if manifest_offset is None:
            return

        if manifest_offset != self._file_table_offset:
            delta = self._file_table_offset - manifest_offset
            sign = "+" if delta >= 0 else ""
            print(
                f"Warning: File table address shifted. "
                f"Expected {format_hex(manifest_offset)}, "
                f"found {format_hex(self._file_table_offset)} "
                f"({sign}{delta} bytes). ROM structure may have been modified.",
                file=sys.stderr,
            )

    def _parse_file_table(self) -> None:
        """Parses the file table entries from the input ROM."""
        self.log(f"Parsing file table at offset {format_hex(self._file_table_offset)}...")

        offset = self._file_table_offset
        entries: list[FileTableEntry] = []
        data_length = len(self._input_data)

        while offset + ENTRY_SIZE_BYTES <= data_length:
            raw_value = read_u32_be(self._input_data, offset)
            entry = FileTableEntry.from_raw(raw_value)
            entries.append(entry)

            # A zero entry terminates the table
            if entry.is_terminator:
                break

            offset += ENTRY_SIZE_BYTES

        self._file_table_entries = entries
        file_count = len(entries) - 1 if entries else 0
        self.log(f"Found {file_count} files (+1 terminator entry).")

    def _validate_file_table(self) -> None:
        """Validates the parsed file table for consistency."""
        if len(self._file_table_entries) < 2:
            raise FileTableError(
                "File table must contain at least one file entry and a terminator."
            )

        # Verify the first file starts within ROM bounds
        first_offset = self._file_table_entries[0].offset
        if first_offset > len(self._input_data):
            raise FileTableError(
                f"First file offset ({format_hex(first_offset)}) exceeds ROM size "
                f"({format_hex(len(self._input_data))})."
            )

    def _initialize_output(self) -> None:
        """Initializes the output buffer with ROM header and metadata."""
        # Copy everything from ROM start up to the first file
        # This preserves the header, signature, and file table space
        first_file_offset = self._file_table_entries[0].offset
        self._output_data = bytearray(self._input_data[:first_file_offset])
        self._output_entries = []

    def _iter_files(self) -> Generator[FileInfo, None, None]:
        """
        Iterates over files described by the file table.

        Each file's data span is determined by the current entry's offset
        and the next entry's offset (files are sequential with no gaps).
        The terminator entry is not yielded.

        Yields:
            FileInfo objects containing file index, data, and metadata.

        Raises:
            FileTableError: If file offsets are out of bounds.
        """
        entries = self._file_table_entries
        rom_size = len(self._input_data)

        # Iterate all entries except the terminator
        for i in range(len(entries) - 1):
            current = entries[i]
            next_entry = entries[i + 1]

            start = current.offset
            end = next_entry.offset

            if start > rom_size or end > rom_size:
                raise FileTableError(
                    f"File {i} has out-of-bounds offsets: "
                    f"{format_hex(start)} - {format_hex(end)} "
                    f"(ROM size: {format_hex(rom_size)})"
                )

            file_data = bytes(self._input_data[start:end])
            yield FileInfo(index=i, data=file_data, entry=current)

    def _process_decompression(self) -> None:
        """Decompresses all compressed files in the ROM."""
        manifest_entries: list[FileManifestEntry] = []
        current_offset = len(self._output_data)

        file_count = len(self._file_table_entries) - 1
        progress = ProgressBar(file_count, verbose=self.config.verbose)

        for file_info in self._iter_files():
            original_size = len(file_info.data)
            output_data = file_info.data
            action = "Copied"

            if file_info.entry.is_compressed and not file_info.is_empty:
                try:
                    output_data = lzkn64.decompress(file_info.data)
                    action = "Decompressed"
                except Exception as e:
                    raise CompressionError(
                        f"Failed to decompress file {file_info.index}: {e}"
                    ) from e

            # Create manifest entry with full metadata
            manifest_entry = FileManifestEntry(
                index=file_info.index,
                compressed=file_info.entry.is_compressed,
                original_offset=file_info.entry.offset,
                original_size=original_size,
                decompressed_size=len(output_data),
                decompressed_crc32=calculate_crc32(output_data),
            )
            manifest_entries.append(manifest_entry)

            self.log(
                f"  File {file_info.index}: {action} "
                f"({original_size:,} -> {len(output_data):,} bytes)"
            )

            self._output_data.extend(output_data)

            # Decompressed output is marked as uncompressed
            self._output_entries.append(current_offset)
            current_offset += len(output_data)

            progress.update()

        progress.finish()
        self._append_terminator(current_offset)

        # Save manifest for future recompression
        self.manifest.save(
            self._file_table_offset,
            manifest_entries,
            verbose=self.config.verbose,
        )

    def _process_compression(self) -> None:
        """Compresses files according to the manifest."""
        current_offset = len(self._output_data)
        stats = CompressionStats()

        file_count = len(self._file_table_entries) - 1
        progress = ProgressBar(file_count, verbose=self.config.verbose)

        # Check manifest file count matches
        if self.manifest.file_count > 0 and self.manifest.file_count != file_count:
            print(
                f"Warning: Manifest has {self.manifest.file_count} entries, "
                f"but ROM has {file_count} files.",
                file=sys.stderr,
            )

        for file_info in self._iter_files():
            manifest_entry = self.manifest.get_entry(file_info.index)

            # Determine if we should compress this file
            should_compress = False
            original_compressed_size = len(file_info.data)

            if manifest_entry is not None:
                should_compress = manifest_entry.compressed
                original_compressed_size = manifest_entry.original_size

                # Verify file if requested
                if self.config.verify:
                    self._verify_file(file_info, manifest_entry, stats)

            output_data = file_info.data
            is_compressed_output = False
            action = "Copied"

            # Compress only if:
            # - Input is not already compressed (we're working from decompressed ROM)
            # - File is not empty
            # - Manifest indicates compression is desired
            can_compress = (
                not file_info.entry.is_compressed
                and not file_info.is_empty
                and should_compress
            )

            if can_compress:
                try:
                    compressed = lzkn64.compress(file_info.data)
                    # Align to 2-byte boundary for N64
                    output_data = align_to_boundary(compressed, N64_ALIGNMENT)
                    is_compressed_output = True
                    action = "Compressed"

                    # Track compression stats
                    stats.add_compressed(
                        file_info.index,
                        original_compressed_size,
                        len(output_data),
                    )
                except Exception as e:
                    raise CompressionError(
                        f"Failed to compress file {file_info.index}: {e}"
                    ) from e
            else:
                stats.add_copied(len(output_data))

            self.log(
                f"  File {file_info.index}: {action} "
                f"({len(file_info.data):,} -> {len(output_data):,} bytes)"
            )

            self._output_data.extend(output_data)

            # Build output entry with appropriate compression flag
            entry_value = current_offset
            if is_compressed_output:
                entry_value |= COMPRESSED_FLAG

            self._output_entries.append(entry_value)
            current_offset += len(output_data)

            progress.update()

        progress.finish()
        self._append_terminator(current_offset)

        # Report statistics
        if self.config.verbose or stats.size_warnings:
            stats.report(verbose=self.config.verbose)

    def _verify_file(
        self,
        file_info: FileInfo,
        manifest_entry: FileManifestEntry,
        stats: CompressionStats,
    ) -> None:
        """
        Verifies a file against its manifest entry.

        Logs warnings for any discrepancies found.
        """
        matches, issues = manifest_entry.matches_data(file_info.data)

        if not matches:
            stats.files_modified += 1
            issues_str = "; ".join(issues)
            print(
                f"  File {file_info.index}: Modified - {issues_str}",
                file=sys.stderr,
            )

    def _append_terminator(self, final_offset: int) -> None:
        """
        Appends the terminator entry to the output file table.

        Preserves the original terminator style (zero vs. final offset).
        """
        last_entry = self._file_table_entries[-1]
        if last_entry.is_terminator:
            self._output_entries.append(0)
        else:
            self._output_entries.append(final_offset)

    def _write_file_table_to_output(self) -> None:
        """Writes the new file table entries to the output buffer."""
        self.log(f"Writing file table at offset {format_hex(self._file_table_offset)}...")

        offset = self._file_table_offset
        for value in self._output_entries:
            if offset + ENTRY_SIZE_BYTES > len(self._output_data):
                raise FileTableError(
                    "File table extends beyond output buffer. "
                    "This indicates a logic error or corrupted input."
                )
            write_u32_be(self._output_data, offset, value)
            offset += ENTRY_SIZE_BYTES

    def _apply_power_of_two_padding(self) -> None:
        """Pads the output buffer to the nearest power of two size."""
        current_size = len(self._output_data)
        target_size = round_up_to_power_of_two(current_size)

        if target_size > current_size:
            padding = target_size - current_size
            self.log(f"Padding output from {current_size:,} to {target_size:,} bytes.")
            self._output_data.extend(b"\x00" * padding)

    def _write_output(self) -> None:
        """Writes the output buffer to the output file."""
        self.log(f"Writing output to: {self.config.output_path}")

        try:
            self.config.output_path.parent.mkdir(parents=True, exist_ok=True)
            with self.config.output_path.open("wb") as f:
                f.write(self._output_data)
        except OSError as e:
            raise RommyError(f"Failed to write output file: {e}") from e

        self.log(f"Wrote {len(self._output_data):,} bytes.")

    def _update_header_crcs(self) -> None:
        """Recalculates and updates the N64 ROM header CRCs."""
        self.log("Calculating N64 header CRCs...")
        try:
            update_n64_header_crcs(self._output_data, verbose=self.config.verbose)
        except RommyError:
            # ROM might be too small (e.g., partial extraction)
            # Log warning but don't fail
            print(
                "Warning: ROM too small for N64 header CRC calculation. "
                "Header CRCs not updated.",
                file=sys.stderr,
            )


# =============================================================================
# Command-Line Interface
# =============================================================================


def create_argument_parser() -> argparse.ArgumentParser:
    """Creates and configures the argument parser."""
    parser = argparse.ArgumentParser(
        description=(
            "Tool to compress/decompress Nintendo 64 ROMs using the "
            "Nisitenma-Ichigo file table format (common in Konami games)."
        ),
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""\
Examples:
  Decompress a ROM (auto-detects file table via signature):
    %(prog)s decompress -i game.z64 -o game_dec.z64 -m manifest.yaml

  Recompress using saved manifest:
    %(prog)s compress -i game_dec.z64 -o game.z64 -m manifest.yaml

  Recompress with file verification:
    %(prog)s compress -i game_dec.z64 -o game.z64 -m manifest.yaml --verify

  Manually specify file table address (if auto-detection fails):
    %(prog)s decompress -i game.z64 -o out.z64 -a 0x12345

The 'Nisitenma-Ichigo' signature is automatically detected in the ROM.
The manifest file preserves file metadata for round-trip processing.
        """,
    )

    subparsers = parser.add_subparsers(
        dest="command",
        required=True,
        metavar="COMMAND",
    )

    # Shared arguments
    common_parser = argparse.ArgumentParser(add_help=False)
    common_parser.add_argument(
        "-i",
        "--input",
        required=True,
        metavar="FILE",
        help="Input ROM file path.",
    )
    common_parser.add_argument(
        "-o",
        "--output",
        required=True,
        metavar="FILE",
        help="Output ROM file path.",
    )
    common_parser.add_argument(
        "-m",
        "--manifest",
        metavar="FILE",
        help="Manifest YAML file for storing/loading file metadata.",
    )
    common_parser.add_argument(
        "-a",
        "--address",
        type=lambda x: int(x, 0),
        metavar="ADDR",
        help=(
            "Override file table offset in ROM (hex or decimal). "
            "If not specified, auto-detected via Nisitenma-Ichigo signature."
        ),
    )
    common_parser.add_argument(
        "-p",
        "--pad",
        action="store_true",
        help="Pad output file size to nearest power of two.",
    )
    common_parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="Enable verbose output with per-file logging.",
    )

    # Decompress command
    subparsers.add_parser(
        "decompress",
        parents=[common_parser],
        help="Decompress all compressed files in a ROM.",
    )

    # Compress command (with verify option)
    compress_parser = subparsers.add_parser(
        "compress",
        parents=[common_parser],
        help="Compress files in a decompressed ROM according to manifest.",
    )
    compress_parser.add_argument(
        "--verify",
        action="store_true",
        help=(
            "Verify files and structure against manifest. "
            "Checks file sizes, checksums, and file table address. "
            "Warns if anything has been modified or shifted."
        ),
    )
    common_parser.add_argument(
        "--no-fix-crcs",
        dest="fix_crcs",
        action="store_false",
        default=True,
        help="Skip recalculating N64 ROM header CRCs.",
    )

    return parser


def main() -> int:
    """
    Main entry point for the command-line interface.

    Returns:
        Exit code: 0 for success, 1 for errors, 130 for keyboard interrupt.
    """
    parser = create_argument_parser()
    args = parser.parse_args()

    try:
        config = RommyConfig.from_args(args)
        rommy = Rommy(config)
        rommy.run()
        return 0
    except RommyError as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1
    except KeyboardInterrupt:
        print("\nOperation cancelled.", file=sys.stderr)
        return 130


if __name__ == "__main__":
    sys.exit(main())