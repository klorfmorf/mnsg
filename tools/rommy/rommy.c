#include "rommy.h"
#include "types.h"
#include "structs.h"
#include "../lzkn64/lzkn64.h"

#include <byteswap.h>
#include <stdlib.h>
#include <string.h>

bool rommy_read_file_address_table(const u8* input_rom_buffer, const u8* reference_rom_buffer, FileAddressTable* file_address_table, const size_t input_rom_buffer_size, const size_t reference_rom_buffer_size, const size_t file_address_table_rom_address) {
    FileAddressTableEntry* input_entry = (FileAddressTableEntry*)(input_rom_buffer + file_address_table_rom_address);
    size_t index = 0;
    
    while (bswap_32(input_entry->start_rom_address) != 0) {
        if ((bswap_32(input_entry->start_rom_address) & 0x7FFFFFFF) > input_rom_buffer_size || (bswap_32(input_entry->end_rom_address) & 0x7FFFFFFF) > input_rom_buffer_size) {
            // Most likely an invalid table, abort.
            return false;
        }

        index++;

        input_entry = (FileAddressTableEntry*)(input_rom_buffer + file_address_table_rom_address + (index * sizeof(u32)));
    }
    
    size_t file_address_table_size = index + 1;

    file_address_table->size = file_address_table_size;
    file_address_table->rom_addresses = calloc(file_address_table->size, sizeof(u32));
    file_address_table->is_compressed_in_reference = calloc(file_address_table->size, sizeof(bool));

    input_entry = (FileAddressTableEntry*)(input_rom_buffer + file_address_table_rom_address);

    FileAddressTableEntry* reference_entry = NULL;
    if (reference_rom_buffer) {
        reference_entry = (FileAddressTableEntry*)(reference_rom_buffer + file_address_table_rom_address);
    }

    for (index = 0; index < file_address_table->size; index++) {
        file_address_table->rom_addresses[index] = bswap_32(input_entry->start_rom_address);

        if (reference_rom_buffer) {
            if ((bswap_32(reference_entry->start_rom_address) & 0x7FFFFFFF) > reference_rom_buffer_size || (bswap_32(reference_entry->end_rom_address) & 0x7FFFFFFF) > reference_rom_buffer_size) {
                // Most likely an invalid table, abort.
                return false;
            }

            file_address_table->is_compressed_in_reference[index] = bswap_32(reference_entry->start_rom_address) >> 31;

            reference_entry = (FileAddressTableEntry*)(reference_rom_buffer + file_address_table_rom_address + (index * sizeof(u32)));
        }

        input_entry = (FileAddressTableEntry*)(input_rom_buffer + file_address_table_rom_address + (index * sizeof(u32)));
    }

    return true;
}

bool rommy_write_file_address_table(const u8* rom_buffer, const FileAddressTable* file_address_table, const size_t rom_buffer_size, const size_t file_address_table_rom_address) {
    FileAddressTableEntry* entry = (FileAddressTableEntry*)(rom_buffer + file_address_table_rom_address);

    for (size_t index = 0; index < file_address_table->size; index++) {
        if ((file_address_table->rom_addresses[index] & 0x7FFFFFFF) > rom_buffer_size) {
            // Most likely an invalid table, abort.
            return false;
        }

        entry->start_rom_address = bswap_32(file_address_table->rom_addresses[index]);

        entry = (FileAddressTableEntry*)(rom_buffer + file_address_table_rom_address + (index * sizeof(u32)));
    }

    return true;
}

size_t rommy_compress(const u8* input_rom_buffer, u8* output_rom_buffer, const FileAddressTable* input_file_address_table, FileAddressTable* output_file_address_table, const size_t input_rom_buffer_size, const size_t output_rom_buffer_size) {
    for (size_t index = 0; index < input_file_address_table->size; index++) {
        if (index == (input_file_address_table->size - 1)) {
            // Reached last entry in table (which is only an end address), break.
            break;
        }

        const FileAddressTableEntry* input_entry = (const FileAddressTableEntry*)(input_file_address_table->rom_addresses + index);
        if ((input_entry->start_rom_address & 0x7FFFFFFF) > input_rom_buffer_size || (input_entry->end_rom_address & 0x7FFFFFFF) > input_rom_buffer_size) {
            // Something went wrong...
            break;
        }

        FileAddressTableEntry* output_entry = (FileAddressTableEntry*)(output_file_address_table->rom_addresses + index);
        if ((output_entry->start_rom_address & 0x7FFFFFFF) > output_rom_buffer_size || (output_entry->end_rom_address & 0x7FFFFFFF) > output_rom_buffer_size) {
            // Something went wrong...
            break;
        }

        bool is_compressed = (input_entry->start_rom_address) >> 31;
        bool is_empty_file = !((input_entry->end_rom_address - input_entry->start_rom_address) & 0x7FFFFFFF);
        if (is_compressed || is_empty_file || !input_file_address_table->is_compressed_in_reference[index]) {
            // File is already compressed, don't bother compressing but update entry.
            u32 compressed_file_size = (input_entry->end_rom_address - input_entry->start_rom_address) & 0x7FFFFFFF;

            memcpy(output_rom_buffer + (output_entry->start_rom_address & 0x7FFFFFFF), input_rom_buffer + (input_entry->start_rom_address & 0x7FFFFFFF), compressed_file_size);

            // Don't need to set the bit here because the flag is already set.
            output_entry->end_rom_address = output_entry->start_rom_address + compressed_file_size;
            continue;
        }

        size_t uncompressed_file_size = (input_entry->end_rom_address - input_entry->start_rom_address) & 0x7FFFFFFF;
        u8* uncompressed_file_buffer = malloc(uncompressed_file_size);

        memcpy(uncompressed_file_buffer, input_rom_buffer + (input_entry->start_rom_address & 0x7FFFFFFF), uncompressed_file_size);

        size_t compressed_file_size = 0x4000000;
        u8* compressed_file_buffer = malloc(compressed_file_size);

        compressed_file_size = lzkn64_compress_accurate(uncompressed_file_buffer, compressed_file_buffer, uncompressed_file_size);

        // Pad the file to a 2-byte boundary.
        compressed_file_size = (compressed_file_size + 1) & ~1;

        memcpy(output_rom_buffer + (output_entry->start_rom_address & 0x7FFFFFFF), compressed_file_buffer, compressed_file_size);

        free(uncompressed_file_buffer);
        free(compressed_file_buffer);

        output_entry->start_rom_address = output_entry->start_rom_address | (1 << 31);
        output_entry->end_rom_address = (output_entry->start_rom_address & 0x7FFFFFFF) + compressed_file_size;
    }

    return output_file_address_table->rom_addresses[output_file_address_table->size - 1];
}

size_t rommy_decompress(const u8* input_rom_buffer, u8* output_rom_buffer, const FileAddressTable* input_file_address_table, FileAddressTable* output_file_address_table, const size_t input_rom_buffer_size, const size_t output_rom_buffer_size) {
    for (size_t index = 0; index < input_file_address_table->size; index++) {
        if (index == (input_file_address_table->size - 1)) {
            // Reached last entry in table (which is only an end address), break.
            break;
        }

        FileAddressTableEntry* input_entry = (FileAddressTableEntry*)(input_file_address_table->rom_addresses + index);
        if ((input_entry->start_rom_address & 0x7FFFFFFF) > input_rom_buffer_size || (input_entry->end_rom_address & 0x7FFFFFFF)  > input_rom_buffer_size) {
            // Something went wrong...
            break;
        }

        FileAddressTableEntry* output_entry = (FileAddressTableEntry*)(output_file_address_table->rom_addresses + index);
        if ((output_entry->start_rom_address & 0x7FFFFFFF) > output_rom_buffer_size || (output_entry->end_rom_address & 0x7FFFFFFF) > output_rom_buffer_size) {
            // Something went wrong...
            break;
        }

        bool is_compressed = (input_entry->start_rom_address) >> 31;
        bool is_empty_file = !((input_entry->end_rom_address - input_entry->start_rom_address) & 0x7FFFFFFF);
        if (!is_compressed || is_empty_file) {
            // File is uncompressed, don't bother decompressing but update entry.
            u32 uncompressed_file_size = (input_entry->end_rom_address - input_entry->start_rom_address) & 0x7FFFFFFF;

            memcpy(output_rom_buffer + output_entry->start_rom_address, input_rom_buffer + input_entry->start_rom_address, uncompressed_file_size);

            // Don't need to mask the address here because the flag is already unset.
            output_entry->end_rom_address = output_entry->start_rom_address + uncompressed_file_size;
            continue;
        }

        size_t compressed_file_size = (input_entry->end_rom_address - input_entry->start_rom_address) & 0x7FFFFFFF;
        u8* compressed_file_buffer = malloc(compressed_file_size);

        memcpy(compressed_file_buffer, input_rom_buffer + (input_entry->start_rom_address & 0x7FFFFFFF), compressed_file_size);

        size_t decompressed_file_size = 0x4000000;
        u8* decompressed_file_buffer = malloc(decompressed_file_size);

        decompressed_file_size = lzkn64_decompress(compressed_file_buffer, decompressed_file_buffer, compressed_file_size);

        memcpy(output_rom_buffer + (output_entry->start_rom_address & 0x7FFFFFFF), decompressed_file_buffer, decompressed_file_size);

        free(compressed_file_buffer);
        free(decompressed_file_buffer);

        output_entry->start_rom_address = output_entry->start_rom_address & 0x7FFFFFFF;
        output_entry->end_rom_address = (output_entry->start_rom_address & 0x7FFFFFFF) + decompressed_file_size;
    }

    return output_file_address_table->rom_addresses[output_file_address_table->size - 1];
}