import sys
import struct

def read_entry(rom_buffer, table_address, index):
    return struct.unpack(">II", rom_buffer[table_address + (index * 8):table_address + (index * 8) + 8])

def main():
    rom = open(sys.argv[1], "rb")
    rom_buffer = rom.read()

    # Address of the file segment table.
    file_segment_table = int(sys.argv[2])

    # Number of entries in the file segment table.
    num_entries = int(sys.argv[3])

    for i in range(num_entries):
        start, end = read_entry(rom_buffer, file_segment_table, i)
        
        if start >= 0x00000000 and start <= 0x7FFFFFFF:
            is_tlb_mapped = True
        else:
            is_tlb_mapped = False

        print(f"Entry {i + 1}: start = {hex(start)}, end = {hex(end)}, TLB mapped = {is_tlb_mapped}")

    rom.close()

if __name__ == '__main__':
    main()