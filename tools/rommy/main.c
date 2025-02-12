#include "main.h"
#include "rommy.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* TODO: Instead of using a ROM as a reference, use some kind of a file that gets output when decompressing the ROM. */

bool parse_arguments(int argc, const char* argv[], Arguments* arguments) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) {
            if (arguments->input_file)  {
                return false;
            }

            arguments->input_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0) {
            if (arguments->output_file)  {
                return false;
            }

            arguments->output_file = argv[++i];
        } else if (strcmp(argv[i], "-r") == 0) {
            if (arguments->reference_file)  {
                return false;
            }

            arguments->reference_file = argv[++i];
        } else if (strcmp(argv[i], "-c") == 0) {
            if (arguments->mode != MODE_UNDEFINED) {
                return false;
            }

            arguments->mode = MODE_COMPRESS;
        } else if (strcmp(argv[i], "-d") == 0) {
            if (arguments->mode != MODE_UNDEFINED) {
                return false;
            }

            arguments->mode = MODE_DECOMPRESS;
        } else if (strcmp(argv[i], "-a") == 0) {
            if (arguments->file_address_table_rom_address) {
                return false;
            }

            arguments->file_address_table_rom_address = strtol(argv[++i], NULL, 0);
        } else if (strcmp(argv[i], "-p") == 0) {
            if (arguments->pad_output) {
                return false;
            }

            arguments->pad_output = true;
        }
    }

    // Check if the required arguments are set.
    if (arguments->mode == MODE_UNDEFINED || !arguments->input_file || !arguments->output_file || !arguments->file_address_table_rom_address) {
        printf("Error: You must specify a mode (compression/decompression), an input file, an output file and the offset of the file address table in ROM.\n");
        return false;
    }

    /*
    if (argc < 5) {
        return false;
    }

    if (strcmp(argv[1], "-c") == 0) {
        arguments->mode = MODE_COMPRESS;
    } else if (strcmp(argv[1], "-d") == 0) {
        arguments->mode = MODE_DECOMPRESS;
    } else {
        return false;
    }

    arguments->input_file = argv[2];
    arguments->output_file = argv[3];
    arguments->file_address_table_rom_address = strtol(argv[4], NULL, 0);

    for (int i = 5; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            arguments->pad_output = true;
        } else {
            return false;
        }
    }
    */

    return true;
}

void print_help(void) {
    printf("Usage: rommy -i <Path to the input ROM file> -o <Path to the output ROM file> (EITHER -c OR -d) -a <Offset of the file address table in ROM> [-r <Path to reference ROM file>] [-p]\n");
    printf("Compress or decompress a Nisitenma-Ichigo title using rommy.\n");
    printf("\n");
    printf("  -i  Specifies the path to the input ROM file.\n");
    printf("  -o  Specifies the path to the output ROM file.\n");
    printf("  -r  Specifies the path to the reference ROM file. Used to skip file compression on specific files so that the output ROM matches.\n");
    printf("  -c  Compress the input file and save it to the output file.\n");
    printf("  -d  Decompress the input file and save it to the output file.\n");
    printf("  -a  Specifies the file address table offset in ROM.\n");
    printf("  -p  Pad the output file to the nearest power of two.\n");
}

int main(int argc, const char* argv[]) {
    Arguments arguments;
    arguments.mode = MODE_UNDEFINED;
    arguments.input_file = NULL;
    arguments.output_file = NULL;
    arguments.reference_file = NULL;
    arguments.file_address_table_rom_address = 0;
    arguments.pad_output = false;

    if (!parse_arguments(argc, argv, &arguments)) {
        print_help();
        return EXIT_FAILURE;
    }

    FILE* input_file = fopen(arguments.input_file, "rb");
    if (input_file == NULL) {
        printf("Error: Could not open input file.\n");
        return EXIT_FAILURE;
    }

    fseek(input_file, 0, SEEK_END);
    size_t input_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    u8* input_buffer = malloc(input_size);
    if (input_buffer == NULL) {
        printf("Error: Could not allocate memory for input buffer.\n");
        return EXIT_FAILURE;
    }

    if (fread(input_buffer, 1, input_size, input_file) != input_size) {
        printf("Error: Could not read input file.\n");
        return EXIT_FAILURE;
    }

    fclose(input_file);

    FILE* reference_file = NULL;
    u8* reference_buffer = NULL;
    size_t reference_size = 0;

    if (arguments.reference_file) {
        reference_file = fopen(arguments.reference_file, "rb");
        if (reference_file == NULL) {
            printf("Error: Could not open reference file.\n");
            return EXIT_FAILURE;
        }

        fseek(reference_file, 0, SEEK_END);
        reference_size = ftell(reference_file);
        fseek(reference_file, 0, SEEK_SET);

        reference_buffer = malloc(reference_size);
        if (reference_buffer == NULL) {
            printf("Error: Could not allocate memory for reference buffer.\n");
            return EXIT_FAILURE;
        }

        if (fread(reference_buffer, 1, reference_size, reference_file) != reference_size) {
            printf("Error: Could not read reference file.\n");
            return EXIT_FAILURE;
        }

        fclose(reference_file);
    }

    if (arguments.file_address_table_rom_address >= input_size) {
        printf("Error: File address table offset exceeds input ROM size.\n");
        return EXIT_FAILURE;
    }

    FileAddressTable input_file_address_table;
    if (!rommy_read_file_address_table(input_buffer, reference_buffer, &input_file_address_table, input_size, reference_size, arguments.file_address_table_rom_address)) {
        printf("Error: Could not read file address table.\n");
        return EXIT_FAILURE;
    }

    FileAddressTable output_file_address_table;
    output_file_address_table.size = input_file_address_table.size;
    output_file_address_table.rom_addresses = calloc(output_file_address_table.size, sizeof(u32));
    output_file_address_table.is_compressed_in_reference = calloc(output_file_address_table.size, sizeof(bool));
    memcpy(output_file_address_table.rom_addresses, input_file_address_table.rom_addresses, input_file_address_table.size * sizeof(u32));
    memcpy(output_file_address_table.is_compressed_in_reference, input_file_address_table.is_compressed_in_reference, input_file_address_table.size * sizeof(bool));

    size_t output_size = ROMMY_MAXIMUM_ROM_SIZE;
    u8 *output_buffer = malloc(output_size);
    memcpy(output_buffer, input_buffer, input_size);

    if (arguments.mode == MODE_COMPRESS) {
        output_size = rommy_compress(input_buffer, output_buffer, &input_file_address_table, &output_file_address_table, input_size, output_size);
    } else if (arguments.mode == MODE_DECOMPRESS) {
        output_size = rommy_decompress(input_buffer, output_buffer, &input_file_address_table, &output_file_address_table, input_size, output_size);
    } else {
        printf("Error: Invalid mode.\n");
        return EXIT_FAILURE;
    }

    if (arguments.pad_output) {
        size_t nearest_power_of_two_size = output_size;

        // https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
        nearest_power_of_two_size -= 1;
        nearest_power_of_two_size |= (nearest_power_of_two_size >> 1);
        nearest_power_of_two_size |= (nearest_power_of_two_size >> 2);
        nearest_power_of_two_size |= (nearest_power_of_two_size >> 4);
        nearest_power_of_two_size |= (nearest_power_of_two_size >> 8);
        nearest_power_of_two_size |= (nearest_power_of_two_size >> 16);
        nearest_power_of_two_size += 1;

        // Zero out any remaining data since the input ROM file might have data left after the file data.
        memset(output_buffer + output_size, 0, nearest_power_of_two_size);

        output_size = nearest_power_of_two_size;
    }

    if (!rommy_write_file_address_table(output_buffer, &output_file_address_table, output_size, arguments.file_address_table_rom_address)) {
        printf("Error: Could not write file address table to output file.\n");
        return EXIT_FAILURE;
    }

    FILE* output_file = fopen(arguments.output_file, "wb");
    if (output_file == NULL) {
        printf("Error: Could not open output file.\n");
        return EXIT_FAILURE;
    }

    if (fwrite(output_buffer, 1, output_size, output_file) != output_size) {
        printf("Error: Could not write output file.\n");
        return EXIT_FAILURE;
    }

    fclose(output_file);

    free(input_buffer);
    free(input_file_address_table.rom_addresses);
    
    free(output_buffer);
    free(output_file_address_table.rom_addresses);

    return EXIT_SUCCESS;
}
