#ifndef ROMMY_H
#define ROMMY_H

#include "types.h"
#include "structs.h"

bool rommy_read_file_address_table(const u8* input_rom_buffer, const u8* reference_rom_buffer, FileAddressTable* file_address_table, const size_t input_rom_buffer_size, const size_t reference_rom_buffer_size, const size_t file_address_table_rom_address);
bool rommy_write_file_address_table(const u8* input_rom_buffer, const FileAddressTable* file_address_table, const size_t input_rom_buffer_size, const size_t file_address_table_rom_address);
size_t rommy_compress(const u8* input_rom_buffer, u8* output_rom_buffer, const FileAddressTable* input_file_address_table, FileAddressTable* output_file_address_table, const size_t input_rom_buffer_size, const size_t output_rom_buffer_size);
size_t rommy_decompress(const u8* input_rom_buffer, u8* output_rom_buffer, const FileAddressTable* input_file_address_table, FileAddressTable* output_file_address_table, const size_t input_rom_buffer_size, const size_t output_rom_buffer_size);

#endif // ROMMY_H
