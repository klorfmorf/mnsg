#ifndef STRUCTS_H
#define STRUCTS_H

#include "types.h"

typedef struct {
    u32 start_rom_address;
    u32 end_rom_address;
} FileAddressTableEntry;

typedef struct {
    size_t size;
    u32* rom_addresses;
    bool* is_compressed_in_reference;
} FileAddressTable;

#endif // STRUCTS_H
