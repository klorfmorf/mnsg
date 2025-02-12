file = open('sym.txt', 'r')

for line in file:
    pieces = line.split()
    print(f"{pieces[1]} = 0x{pieces[0]}; // type:func")

file.close()