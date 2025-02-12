import sys

def main():
    file_path = sys.argv[1]

    # A line consists of an address and a symbol name separated by a space.
    # The address is a 32-bit hexadecimal number.

    # Read the input file.
    with open(file_path, 'r') as f:
        lines = f.readlines()

    # Output the symbols using this format: "symbol_name = 0xaddress;"
    for line in lines:
        line = line.strip()
        addr, symbol_name = line.split(' ')
        print(f'{symbol_name} = 0x{addr};')

if __name__ == '__main__':
    main()