import sys

def remove_bss_lines(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    with open(file_path, 'w') as file:
        for line in lines:
            if 'bss' not in line.lower():
                file.write(line)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python remove_bss.py <path_to_yaml_file>")
    else:
        remove_bss_lines(sys.argv[1])
