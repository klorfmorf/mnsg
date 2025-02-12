#ifndef LZKN64_H
#define LZKN64_H

#include "types.h"

#define COMMAND_UNDEFINED 0x7F

// COMMAND_SLIDING_WINDOW
#define COMMAND_SLIDING_WINDOW_COPY 0x00
#define COMMAND_SLIDING_WINDOW_COPY_START 0x00
#define COMMAND_SLIDING_WINDOW_COPY_END 0x7F
#define COMMAND_SLIDING_WINDOW_COPY_LENGTH_MASK 0x7C
#define COMMAND_SLIDING_WINDOW_COPY_OFFSET_FIRST_BYTE_MASK 0x03
#define COMMAND_SLIDING_WINDOW_COPY_OFFSET_SECOND_BYTE_MASK 0xFF
#define COMMAND_SLIDING_WINDOW_COPY_OFFSET_MAX_MASK 0x3FF

// COMMAND_RAW_COPY
#define COMMAND_RAW_COPY 0x80
#define COMMAND_RAW_COPY_START 0x80
#define COMMAND_RAW_COPY_END 0x9F
#define COMMAND_RAW_COPY_LENGTH_MASK 0x1F

// COMMAND_RLE_WRITE_SHORT_ANY_VALUE
#define COMMAND_RLE_WRITE_SHORT_ANY_VALUE 0xC0
#define COMMAND_RLE_WRITE_SHORT_ANY_VALUE_START 0xC0
#define COMMAND_RLE_WRITE_SHORT_ANY_VALUE_END 0xDF
#define COMMAND_RLE_WRITE_SHORT_ANY_VALUE_LENGTH_MASK 0x1F

// COMMAND_RLE_WRITE_SHORT_ZERO
#define COMMAND_RLE_WRITE_SHORT_ZERO 0xE0
#define COMMAND_RLE_WRITE_SHORT_ZERO_START 0xE0
#define COMMAND_RLE_WRITE_SHORT_ZERO_END 0xFE
#define COMMAND_RLE_WRITE_SHORT_ZERO_LENGTH_MASK 0x1F

// COMMAND_RLE_WRITE_LONG_ZERO
#define COMMAND_RLE_WRITE_LONG_ZERO 0xFF
#define COMMAND_RLE_WRITE_LONG_ZERO_START 0xFF
#define COMMAND_RLE_WRITE_LONG_ZERO_END 0xFF
#define COMMAND_RLE_WRITE_LONG_ZERO_LENGTH_MASK 0xFF

// Other constants.
#define SLIDING_WINDOW_SIZE_EFFICIENT 0x3FF
#define SLIDING_WINDOW_SIZE_ACCURATE 0x3DF
#define SLIDING_WINDOW_COPY_MAXIMUM_LENGTH 0x1F + 2
#define RAW_COPY_MAXIMUM_LENGTH 0x1F
#define RLE_SHORT_MAXIMUM_LENGTH 0x1F + 2
#define RLE_LONG_MAXIMUM_LENGTH 0xFF + 2

// Very slightly more efficient compression algorithm that doesn't match the games exactly.
size_t lzkn64_compress_efficient(const u8 *input_buffer, u8 *output_buffer, size_t input_size);

// Matches the compression algorithm used in the actual games exactly.
size_t lzkn64_compress_accurate(const u8 *input_buffer, u8 *output_buffer, size_t input_size);

size_t lzkn64_decompress(const u8 *input_buffer, u8 *output_buffer, size_t input_size);

#endif // LZKN64_H
