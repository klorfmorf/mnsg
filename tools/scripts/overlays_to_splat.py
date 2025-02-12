import sys
import struct

def read_file_address_table(rom_buffer, table_address):
    table_entries = []
    table_entry = 0x00000000

    while True:
        table_entry = struct.unpack(">I", rom_buffer[table_address:table_address + 4])[0]

        if table_entry == 0x00000000:
            break

        table_address += 4
        table_entries.append(table_entry & 0x7fffffff)

    return table_entries

def read_file_segment_table_entry(rom_buffer, table_address, index):
    return struct.unpack(">II", rom_buffer[table_address + (index * 8):table_address + (index * 8) + 8])

# Japan:
# file_address_table = 0x58258
# file_segment_table = 0x5594C
# USA:
# file_address_table = 0x57FD8
# file_segment_table = 0x556CC
def main():
    rom = open(sys.argv[1], "rb")
    rom_buffer = rom.read()

    # Address of the file address table.
    file_address_table = int(sys.argv[2], 16)

    # Address of the file segment table.
    file_segment_table = int(sys.argv[3], 16)

    table_entries = read_file_address_table(rom_buffer, file_address_table)

    for i, table_entry in enumerate(table_entries):
        if i == len(table_entries) - 1:
            break

        vram_start = read_file_segment_table_entry(rom_buffer, file_segment_table, i)[0]
        vram_end = read_file_segment_table_entry(rom_buffer, file_segment_table, i)[1]
        table_entry_size = (table_entries[i + 1] & 0x7fffffff) - table_entry
        segment_size = vram_end - vram_start
        has_bss_section = False
        bss_section_size = 0
        is_code_file = False
        exclusive_ram_id = ""
        
        # Skip empty files, files are empty when the start address is the same as the next file.
        if table_entry == table_entries[i + 1]:
            continue

        if segment_size > table_entry_size:
            has_bss_section = True
            bss_section_size = segment_size - table_entry_size

        # Check if the file is a code file (file ids 11-80).
        if (i + 1) >= 11 and (i + 1) <= 80:
            is_code_file = True

        if is_code_file:
            if vram_start == 0x801D0B90 or vram_start == 0x801CB460:
                exclusive_ram_id = "static_overlay_1"
            elif vram_start == 0x80212090 or vram_start == 0x8020D2A0:
                exclusive_ram_id = "static_overlay_2"
            elif vram_start == 0x8000000:
                exclusive_ram_id = "tlb_overlay"
        else:
            vram_segment = (vram_start >> 24) & 0xFF
            exclusive_ram_id = f"asset_{vram_segment}"
        
        print(f"- name: file_{i + 1}")
        print(f"  type: code")
        print(f"  start: {"0x" + hex(table_entry & 0x7fffffff).split("x")[1].upper()}")
        print(f"  vram: {"0x" + hex(vram_start).split("x")[1].upper()}")

        if has_bss_section:
            print(f"  bss_size: {"0x" + hex(bss_section_size).split("x")[1].upper()}")

        print(f"  subalign: 16")
        print(f"  overlay: yes")
        print(f"  exclusive_ram_id: {exclusive_ram_id}")
        print(f"  subsegments:")

        if is_code_file:
            print(f"  - [{"0x" + hex(table_entry & 0x7fffffff).split("x")[1].upper()}, asm]")
        else:
            print(f"  - [{"0x" + hex(table_entry & 0x7fffffff).split("x")[1].upper()}, databin]")

        if has_bss_section:
            print("")
            print("  - { start: 0x" + hex(table_entries[i + 1]).split("x")[1].upper() + ", type: bss, vram: 0x" + hex(vram_start + table_entry_size).split("x")[1].upper() + " }")

        print()

    rom.close()

if __name__ == '__main__':
    main()