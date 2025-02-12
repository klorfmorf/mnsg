CC := gcc
CFLAGS := -Wall -Wextra -O2

# Uncomment the following lines if you want to use clang instead of gcc
# CC := clang
# CFLAGS := -Wall -Wextra -O2

TARGET := n64crc

all: $(TARGET)

$(TARGET): n64crc.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGET)