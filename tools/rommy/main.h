#ifndef MAIN_H
#define MAIN_H

#include "types.h"

#define ROMMY_MAXIMUM_ROM_SIZE 0x4000000 // 512 Mbit (64 Mbyte)

typedef enum {
    MODE_UNDEFINED,
    MODE_COMPRESS,
    MODE_DECOMPRESS
} Mode;

typedef struct {
    Mode mode;
    const char* input_file;
    const char* output_file;
    const char* reference_file;
    u32 file_address_table_rom_address;
    bool pad_output;
} Arguments;

bool parse_arguments(int argc, const char* argv[], Arguments* arguments);
void print_help(void);

#endif // MAIN_H
