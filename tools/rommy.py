#!/usr/bin/env python3
from __future__ import annotations

import argparse
import struct
import sys
import time
import zlib
from collections.abc import Generator
from dataclasses import dataclass
from enum import Enum
from pathlib import Path
from typing import Any

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

NISITENMA_SIGNATURE = b"Nisitenma-Ichigo"
SIGNATURE_LENGTH = len(NISITENMA_SIGNATURE)

OFFSET_MASK = 0x7FFFFFFF
COMPRESSED_FLAG = 0x80000000 
LENGTH_MSB_FLAG = 0x80000000

ZLIB_LEVEL = 9
ZLIB_WBITS = 15
ZLIB_MEM_LEVEL = 8
ZLIB_STRATEGY = 0

ENTRY_SIZE_BYTES = 4
PI_ALIGNMENT = 2

MANIFEST_VERSION = 1

# =============================================================================
# Exceptions
# =============================================================================

class RommyError(Exception):
    """Base exception for all Rommy-related errors."""


class FileTableNotFoundError(RommyError):
    """Raised when the Nisitenma-Ichigo file table cannot be located in the ROM."""


class FileTableError(RommyError):
    """Raised when the file table is invalid or corrupted."""


class CompressionError(RommyError):
    """Raised when compression or decompression fails."""


class ManifestError(RommyError):
    """Raised when manifest reading or writing fails."""

# =============================================================================
# Utility Functions
# =============================================================================

def read_u32_be(buffer: bytes | bytearray, offset: int) -> int:
    """Reads a big-endian unsigned 32-bit integer from the buffer."""
    return struct.unpack_from(">I", buffer, offset)[0]

def write_u32_be(buffer: bytearray, offset: int, value: int) -> None:
    """Writes a big-endian unsigned 32-bit integer to the buffer."""
    struct.pack_into(">I", buffer, offset, value)

def round_up_to_power_of_two(n: int) -> int:
    """Rounds a number up to the nearest power of two."""
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
    """Pads data with null bytes to meet the specified alignment boundary."""
    remainder = len(data) % alignment
    if remainder == 0:
        return data
    return data + (b"\x00" * (alignment - remainder))

def find_nisitenma_signature(data: bytes) -> int:
    """Searches for the Nisitenma-Ichigo signature in ROM data."""
    index = data.find(NISITENMA_SIGNATURE)
    if index == -1:
        raise FileTableNotFoundError(
            "Nisitenma-Ichigo signature not found in ROM. "
            "This ROM may not use the expected file table format, "
            "or you may need to specify the address manually with -a/--address."
        )
    return index

def parse_hex_or_int(value: int | str) -> int:
    """Parses a value that may be an integer or a hex string."""
    if isinstance(value, str):
        return int(value, 0)
    return value

def format_hex(value: int) -> str:
    """Formats an integer as a hexadecimal string with 0x prefix."""
    return f"0x{value:X}"

# =============================================================================
# Data Classes & Enums
# =============================================================================

class CompressionType(str, Enum):
    """
    Supported compression formats in Nisitenma-Ichigo ROMs.
    """

    NONE = "none"
    ZLIB = "zlib"
    LZKN64 = "lzkn64"

    def __str__(self) -> str:
        return self.value

@dataclass(frozen=True)
class CompressionHeader:
    """
    Represents the 4-byte length field found at the start of compressed data.

    Both zlib and lzkn64 compressed streams begin with a 32-bit big-endian field
    encoding the length of the compressed data (including the field itself). 
    The games distinguish the compression format by inspecting the most-significant bit (bit 31):
      - High (bit 31 == 1): zlib compression
      - Low (bit 31 == 0): lzkn64 compression
    """

    raw_value: int

    @classmethod
    def from_data(cls, data: bytes | bytearray) -> CompressionHeader:
        """Reads the 4-byte length field from the beginning of a data chunk."""
        if len(data) < 4:
            return cls(raw_value=0)
        return cls(raw_value=read_u32_be(data, 0))

    @property
    def is_msb_set(self) -> bool:
        """Returns True if the most-significant bit (bit 31) is set."""
        return bool(self.raw_value & LENGTH_MSB_FLAG)

    @property
    def compression_type(self) -> CompressionType:
        """Returns ZLIB if MSB is high, LZKN64 if MSB is low."""
        return CompressionType.ZLIB if self.is_msb_set else CompressionType.LZKN64

    @property
    def compressed_size(self) -> int:
        """Returns the length of the compressed data (lower 31 bits)."""
        return self.raw_value & OFFSET_MASK

@dataclass
class FileTableEntry:
    """Represents a single entry in the Nisitenma-Ichigo file table."""

    offset: int
    is_compressed: bool

    @classmethod
    def from_raw(cls, raw_value: int) -> FileTableEntry:
        return cls(
            offset=raw_value & OFFSET_MASK,
            is_compressed=bool(raw_value & COMPRESSED_FLAG),
        )

    def to_raw(self) -> int:
        value = self.offset & OFFSET_MASK
        if self.is_compressed:
            value |= COMPRESSED_FLAG
        return value

    @property
    def is_terminator(self) -> bool:
        return self.offset == 0 and not self.is_compressed

    def __repr__(self) -> str:
        status = "compressed" if self.is_compressed else "raw"
        return f"FileTableEntry(0x{self.offset:08X}, {status})"

@dataclass
class FileInfo:
    """Contains information about a single file extracted from the ROM."""

    index: int
    data: bytes
    entry: FileTableEntry

    @property
    def is_empty(self) -> bool:
        return len(self.data) == 0

@dataclass
class FileManifestEntry:
    """Manifest entry containing compression metadata for a single file."""

    index: int
    compressed: bool
    compression_type: CompressionType = CompressionType.NONE

    def to_dict(self) -> dict[str, Any]:
        return {
            "index": self.index,
            "compressed": self.compressed,
            "compression_type": self.compression_type.value,
        }

    @classmethod
    def from_dict(cls, data: dict[str, Any]) -> FileManifestEntry:
        is_compressed = bool(data.get("compressed", False))
        comp_type_raw = data.get("compression_type")

        if comp_type_raw is None:
            comp_type = (
                CompressionType.LZKN64 if is_compressed else CompressionType.NONE
            )
        else:
            try:
                comp_type = CompressionType(str(comp_type_raw).lower())
            except ValueError:
                raise ManifestError(
                    f"Unknown compression type '{comp_type_raw}' in manifest."
                )

        return cls(
            index=int(data["index"]),
            compressed=is_compressed,
            compression_type=comp_type,
        )

@dataclass
class CompressionStats:
    """Statistics collected during compression for reporting."""

    files_compressed: int = 0
    files_copied: int = 0
    zlib_count: int = 0
    lzkn64_count: int = 0
    total_input_size: int = 0
    total_output_size: int = 0

    def add_compressed(
        self, comp_type: CompressionType, in_size: int, out_size: int
    ) -> None:
        self.files_compressed += 1
        if comp_type == CompressionType.ZLIB:
            self.zlib_count += 1
        elif comp_type == CompressionType.LZKN64:
            self.lzkn64_count += 1
        self.total_input_size += in_size
        self.total_output_size += out_size

    def add_copied(self, size: int) -> None:
        self.files_copied += 1
        self.total_input_size += size
        self.total_output_size += size

    def report(self) -> None:
        print("\nCompression Statistics:")
        print(f"  Files compressed: {self.files_compressed}")
        if self.zlib_count > 0:
            print(f"    - zlib:         {self.zlib_count}")
        if self.lzkn64_count > 0:
            print(f"    - lzkn64:       {self.lzkn64_count}")
        print(f"  Files copied:     {self.files_copied}")
        if self.total_input_size > 0:
            ratio = self.total_output_size / self.total_input_size
            delta = self.total_output_size - self.total_input_size
            sign = "+" if delta >= 0 else ""
            print(
                f"  Total data size:  {self.total_output_size:,} bytes "
                f"({sign}{delta:,}, {ratio:.2%} of uncompressed)"
            )

# =============================================================================
# Configuration
# =============================================================================

@dataclass
class RommyConfig:
    """Configuration container for Rommy operations."""

    input_path: Path
    output_path: Path
    manifest_path: Path
    command: str
    file_table_address: int | None = None
    pad_output: bool = False
    verbose: bool = False

    @classmethod
    def from_args(
        cls, args: argparse.Namespace, parser: argparse.ArgumentParser
    ) -> RommyConfig:
        # Resolve positional and flag arguments
        positionals = [
            p
            for p in (args.pos_input, args.pos_output, args.pos_manifest)
            if p is not None
        ]

        input_val = args.flag_input
        if not input_val and positionals:
            input_val = positionals.pop(0)

        output_val = args.flag_output
        if not output_val and positionals:
            output_val = positionals.pop(0)

        manifest_val = args.flag_manifest
        if not manifest_val and positionals:
            manifest_val = positionals.pop(0)

        missing = []
        if not input_val:
            missing.append("input ROM (-i/--input or 1st positional)")
        if not output_val:
            missing.append("output ROM (-o/--output or 2nd positional)")
        if not manifest_val:
            missing.append("manifest YAML (-m/--manifest or 3rd positional)")

        if missing:
            parser.error(f"Missing required argument(s): {', '.join(missing)}")

        return cls(
            input_path=Path(input_val),
            output_path=Path(output_val),
            manifest_path=Path(manifest_val),
            command=args.command,
            file_table_address=args.address,
            pad_output=args.pad,
            verbose=args.verbose,
        )

# =============================================================================
# Progress Display
# =============================================================================

class ProgressBar:
    """Console progress bar for tracking operation progress."""

    def __init__(self, total: int, width: int = 50, verbose: bool = False):
        self.total = total
        self.width = width
        self.verbose = verbose
        self._current = 0
        self._start_time = time.time()

    def update(self, step: int = 1) -> None:
        self._current += step
        if not self.verbose:
            self._render()

    def _render(self) -> None:
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
        if not self.verbose:
            sys.stdout.write("\n")
            sys.stdout.flush()

# =============================================================================
# Manifest Handling
# =============================================================================

class Manifest:
    """Handles reading and writing manifest files."""

    def __init__(self, path: Path):
        self.path = path
        self._entries_by_index: dict[int, FileManifestEntry] = {}
        self._file_table_offset: int | None = None

    @property
    def file_count(self) -> int:
        return len(self._entries_by_index)

    @property
    def file_table_offset(self) -> int | None:
        return self._file_table_offset

    def get_entry(self, index: int) -> FileManifestEntry | None:
        return self._entries_by_index.get(index)

    def load(self) -> None:
        """Loads and parses the manifest YAML file."""
        if not self.path.exists():
            raise ManifestError(f"Manifest file not found: {self.path}")

        try:
            with self.path.open("r", encoding="utf-8") as f:
                data = yaml.safe_load(f)
        except yaml.YAMLError as e:
            raise ManifestError(f"Failed to parse manifest YAML: {e}") from e
        except OSError as e:
            raise ManifestError(f"Failed to read manifest file: {e}") from e

        if not isinstance(data, dict):
            raise ManifestError("Manifest root must be a dictionary.")

        version = data.get("version")
        if version != MANIFEST_VERSION:
            raise ManifestError(
                f"Unsupported manifest version '{version}'. "
                f"Expected version {MANIFEST_VERSION}."
            )

        offset_val = data.get("file_table_offset")
        if offset_val is not None:
            self._file_table_offset = parse_hex_or_int(offset_val)

        files_data = data.get("files")
        if not isinstance(files_data, list):
            raise ManifestError("Manifest 'files' key must be a list.")

        try:
            entries = [FileManifestEntry.from_dict(entry) for entry in files_data]
            self._entries_by_index = {entry.index: entry for entry in entries}
        except (KeyError, TypeError, ValueError, ManifestError) as e:
            raise ManifestError(f"Invalid entry in manifest: {e}") from e

    def save(
        self,
        file_table_offset: int,
        entries: list[FileManifestEntry],
        verbose: bool = False,
    ) -> None:
        """Saves manifest data to disk."""
        manifest_data = {
            "version": MANIFEST_VERSION,
            "file_table_offset": format_hex(file_table_offset),
            "files": [entry.to_dict() for entry in entries],
        }

        try:
            if verbose:
                print(f"Writing manifest artifact to: {self.path}")

            self.path.parent.mkdir(parents=True, exist_ok=True)
            with self.path.open("w", encoding="utf-8") as f:
                yaml.dump(manifest_data, f, sort_keys=False, allow_unicode=True)

            self._file_table_offset = file_table_offset
            self._entries_by_index = {entry.index: entry for entry in entries}
        except OSError as e:
            raise ManifestError(f"Failed to write manifest file: {e}") from e

# =============================================================================
# Main ROM Handler
# =============================================================================

class Rommy:
    """Main processor for ROM compression and decompression."""

    def __init__(self, config: RommyConfig):
        self.config = config
        self.manifest = Manifest(config.manifest_path)

        self._input_data: bytearray = bytearray()
        self._output_data: bytearray = bytearray()
        self._file_table_offset: int = 0
        self._file_table_entries: list[FileTableEntry] = []
        self._output_entries: list[int] = []

    def log(self, message: str) -> None:
        if self.config.verbose:
            print(message)

    def run(self) -> None:
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
            self.manifest.load()
            self._process_compression()
        else:
            self._process_decompression()

        self._write_file_table_to_output()

        if self.config.pad_output:
            self._apply_power_of_two_padding()

        self._write_output()
        print("Done!")

    def _load_input(self) -> None:
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
        if self.config.file_table_address is not None:
            self._file_table_offset = self.config.file_table_address
            self.log(
                f"Using provided file table address: "
                f"{format_hex(self._file_table_offset)}"
            )
            return

        self.log("Searching for Nisitenma-Ichigo signature...")
        signature_offset = find_nisitenma_signature(self._input_data)
        self._file_table_offset = signature_offset + SIGNATURE_LENGTH
        self.log(
            f"Found signature at {format_hex(signature_offset)}, "
            f"file table entries at {format_hex(self._file_table_offset)}"
        )

    def _parse_file_table(self) -> None:
        self.log(
            f"Parsing file table at offset {format_hex(self._file_table_offset)}..."
        )
        offset = self._file_table_offset
        entries: list[FileTableEntry] = []
        data_length = len(self._input_data)

        while offset + ENTRY_SIZE_BYTES <= data_length:
            raw_value = read_u32_be(self._input_data, offset)
            entry = FileTableEntry.from_raw(raw_value)
            entries.append(entry)

            if entry.is_terminator:
                break

            offset += ENTRY_SIZE_BYTES

        self._file_table_entries = entries
        file_count = len(entries) - 1 if entries else 0
        self.log(f"Found {file_count} files (+1 terminator entry).")

    def _validate_file_table(self) -> None:
        if len(self._file_table_entries) < 2:
            raise FileTableError(
                "File table must contain at least one file entry and a terminator."
            )

        first_offset = self._file_table_entries[0].offset
        if first_offset > len(self._input_data):
            raise FileTableError(
                f"First file offset ({format_hex(first_offset)}) exceeds ROM size "
                f"({format_hex(len(self._input_data))})."
            )

    def _initialize_output(self) -> None:
        first_file_offset = self._file_table_entries[0].offset
        self._output_data = bytearray(self._input_data[:first_file_offset])
        self._output_entries = []

    def _iter_files(self) -> Generator[FileInfo, None, None]:
        entries = self._file_table_entries
        rom_size = len(self._input_data)

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
        """Decompresses files and outputs the manifest artifact."""
        manifest_entries: list[FileManifestEntry] = []
        current_offset = len(self._output_data)

        file_count = len(self._file_table_entries) - 1
        progress = ProgressBar(file_count, verbose=self.config.verbose)

        for file_info in self._iter_files():
            original_size = len(file_info.data)
            output_data = file_info.data
            action = "Copied"
            compression_type = CompressionType.NONE
            is_compressed = False

            if file_info.entry.is_compressed and not file_info.is_empty:
                is_compressed = True
                # Identify compression format via the 4-byte length field header
                header = CompressionHeader.from_data(file_info.data)
                compression_type = header.compression_type

                if compression_type == CompressionType.ZLIB:
                    try:
                        decompressor = zlib.decompressobj()
                        output_data = decompressor.decompress(file_info.data[4:])
                        action = "Decompressed (zlib)"
                    except Exception as e:
                        raise CompressionError(
                            f"Failed to decompress file {file_info.index} with zlib: {e}"
                        ) from e

                elif compression_type == CompressionType.LZKN64:
                    comp_size = header.compressed_size
                    lzkn_data = (
                        file_info.data[:comp_size]
                        if 0 < comp_size <= len(file_info.data)
                        else file_info.data
                    )
                    try:
                        output_data = lzkn64.decompress(lzkn_data)
                        action = "Decompressed (lzkn64)"
                    except Exception as e:
                        raise CompressionError(
                            f"Failed to decompress file {file_info.index} with lzkn64: {e}"
                        ) from e

            manifest_entries.append(
                FileManifestEntry(
                    index=file_info.index,
                    compressed=is_compressed,
                    compression_type=compression_type,
                )
            )

            self.log(
                f"  File {file_info.index}: {action} "
                f"({original_size:,} -> {len(output_data):,} bytes)"
            )

            self._output_data.extend(output_data)
            # In the decompressed ROM, all files are marked as uncompressed
            self._output_entries.append(current_offset)
            current_offset += len(output_data)

            progress.update()

        progress.finish()
        self._append_terminator(current_offset)

        # Save manifest artifact
        self.manifest.save(
            self._file_table_offset,
            manifest_entries,
            verbose=self.config.verbose,
        )

    def _process_compression(self) -> None:
        """Compresses files according to the manifest artifact."""
        current_offset = len(self._output_data)
        stats = CompressionStats()

        file_count = len(self._file_table_entries) - 1
        if self.manifest.file_count != file_count:
            raise ManifestError(
                f"Manifest entry count ({self.manifest.file_count}) does not match "
                f"ROM file count ({file_count}). The manifest does not match this ROM."
            )

        progress = ProgressBar(file_count, verbose=self.config.verbose)

        for file_info in self._iter_files():
            manifest_entry = self.manifest.get_entry(file_info.index)
            if manifest_entry is None:
                raise ManifestError(
                    f"Manifest missing entry for file index {file_info.index}."
                )

            output_data = file_info.data
            is_compressed_output = False
            action = "Copied"

            if manifest_entry.compressed and not file_info.is_empty:
                # If already compressed in input ROM, preserve it
                if file_info.entry.is_compressed:
                    output_data = file_info.data
                    is_compressed_output = True
                    action = f"Copied ({manifest_entry.compression_type.value})"
                    stats.add_compressed(
                        manifest_entry.compression_type,
                        len(file_info.data),
                        len(output_data),
                    )
                else:
                    if manifest_entry.compression_type == CompressionType.ZLIB:
                        try:
                            compressor = zlib.compressobj(
                                level=ZLIB_LEVEL,
                                method=zlib.DEFLATED,
                                wbits=ZLIB_WBITS,
                                memLevel=ZLIB_MEM_LEVEL,
                                strategy=ZLIB_STRATEGY
                            )
                            compressed = compressor.compress(file_info.data) + compressor.flush()
                            # Set most significant bit in the length field to indicate a zlib compressed file
                            header_val = LENGTH_MSB_FLAG | (len(compressed) + 4)
                            output_data = align_to_boundary(
                                struct.pack(">I", header_val) + compressed,
                                PI_ALIGNMENT,
                            )
                            is_compressed_output = True
                            action = "Compressed (zlib)"
                            stats.add_compressed(
                                CompressionType.ZLIB,
                                len(file_info.data),
                                len(output_data),
                            )
                        except Exception as e:
                            raise CompressionError(
                                f"Failed to compress file {file_info.index} with zlib: {e}"
                            ) from e
                    elif manifest_entry.compression_type == CompressionType.LZKN64:
                        try:
                            compressed = lzkn64.compress(file_info.data)
                            output_data = align_to_boundary(
                                compressed, PI_ALIGNMENT
                            )
                            is_compressed_output = True
                            action = "Compressed (lzkn64)"
                            stats.add_compressed(
                                CompressionType.LZKN64,
                                len(file_info.data),
                                len(output_data),
                            )
                        except Exception as e:
                            raise CompressionError(
                                f"Failed to compress file {file_info.index} with lzkn64: {e}"
                            ) from e
                    else:
                        stats.add_copied(len(output_data))
            else:
                stats.add_copied(len(output_data))

            self.log(
                f"  File {file_info.index}: {action} "
                f"({len(file_info.data):,} -> {len(output_data):,} bytes)"
            )

            self._output_data.extend(output_data)

            entry_value = current_offset
            if is_compressed_output:
                entry_value |= COMPRESSED_FLAG

            self._output_entries.append(entry_value)
            current_offset += len(output_data)

            progress.update()

        progress.finish()
        self._append_terminator(current_offset)
        stats.report()

    def _append_terminator(self, final_offset: int) -> None:
        last_entry = self._file_table_entries[-1]
        if last_entry.is_terminator:
            self._output_entries.append(0)
        else:
            self._output_entries.append(final_offset)

    def _write_file_table_to_output(self) -> None:
        self.log(
            f"Writing file table at offset {format_hex(self._file_table_offset)}..."
        )
        offset = self._file_table_offset
        for value in self._output_entries:
            if offset + ENTRY_SIZE_BYTES > len(self._output_data):
                raise FileTableError(
                    "File table extends beyond output buffer. "
                    "This indicates corrupt offsets or an undersized table header."
                )
            write_u32_be(self._output_data, offset, value)
            offset += ENTRY_SIZE_BYTES

    def _apply_power_of_two_padding(self) -> None:
        current_size = len(self._output_data)
        target_size = round_up_to_power_of_two(current_size)

        if target_size > current_size:
            padding = target_size - current_size
            self.log(
                f"Padding output from {current_size:,} to {target_size:,} bytes."
            )
            self._output_data.extend(b"\x00" * padding)

    def _write_output(self) -> None:
        self.log(f"Writing output to: {self.config.output_path}")
        try:
            self.config.output_path.parent.mkdir(parents=True, exist_ok=True)
            with self.config.output_path.open("wb") as f:
                f.write(self._output_data)
        except OSError as e:
            raise RommyError(f"Failed to write output file: {e}") from e

        self.log(f"Wrote {len(self._output_data):,} bytes.")

# =============================================================================
# Command-Line Interface
# =============================================================================

def _add_common_arguments(parser: argparse.ArgumentParser) -> None:
    # Positional arguments
    parser.add_argument(
        "pos_input",
        nargs="?",
        metavar="INPUT",
        help="Input ROM file path.",
    )
    parser.add_argument(
        "pos_output",
        nargs="?",
        metavar="OUTPUT",
        help="Output ROM file path.",
    )
    parser.add_argument(
        "pos_manifest",
        nargs="?",
        metavar="MANIFEST",
        help="Manifest YAML file path.",
    )

    # Flag arguments
    parser.add_argument(
        "-i",
        "--input",
        dest="flag_input",
        metavar="FILE",
        help="Input ROM file path.",
    )
    parser.add_argument(
        "-o",
        "--output",
        dest="flag_output",
        metavar="FILE",
        help="Output ROM file path.",
    )
    parser.add_argument(
        "-m",
        "--manifest",
        dest="flag_manifest",
        metavar="FILE",
        help="Manifest YAML file path.",
    )
    parser.add_argument(
        "-a",
        "--address",
        type=lambda x: int(x, 0),
        metavar="ADDR",
        help=(
            "Override file table offset in ROM (hex or decimal). "
            "If not specified, auto-detected via Nisitenma-Ichigo signature."
        ),
    )
    parser.add_argument(
        "-p",
        "--pad",
        action="store_true",
        help="Pad output file size to nearest power of two.",
    )
    parser.add_argument(
        "-v",
        "--verbose",
        action="store_true",
        help="Enable verbose output with per-file logging.",
    )


def create_argument_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Tool to compress/decompress Nintendo 64 ROMs using the "
            "Nisitenma-Ichigo file table format."
        ),
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""\
Examples:
  Decompress a ROM (produces manifest artifact):
    %(prog)s decompress game.z64 game_dec.z64 manifest.yaml
    %(prog)s decompress -i game.z64 -o game_dec.z64 -m manifest.yaml

  (Re)compress a ROM (using saved manifest):
    %(prog)s compress game_dec.z64 game.z64 manifest.yaml
    %(prog)s compress -i game_dec.z64 -o game.z64 -m manifest.yaml

  Manually specify file table address (if auto-detection fails):
    %(prog)s decompress game.z64 game_dec.z64 manifest.yaml -a 0x2A96C
        """,
    )

    subparsers = parser.add_subparsers(
        dest="command",
        required=True,
        metavar="COMMAND",
    )

    decompress_parser = subparsers.add_parser(
        "decompress",
        help="Decompress all compressed files in a ROM and produce manifest.",
    )
    _add_common_arguments(decompress_parser)

    compress_parser = subparsers.add_parser(
        "compress",
        help="Compress all files in a ROM according to the manifest artifact.",
    )
    _add_common_arguments(compress_parser)

    return parser

def main() -> int:
    parser = create_argument_parser()
    args = parser.parse_args()

    try:
        config = RommyConfig.from_args(args, parser)
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