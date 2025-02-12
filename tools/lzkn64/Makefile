# Makefile for lzkn64

CC := gcc
CFLAGS := -Wall -Wextra -O2

# Uncomment the following lines if you want to use clang instead of gcc
# CC := clang
# CFLAGS := -Wall -Wextra -O2

OBJS = lzkn64.o main.o
LIB_OBJS = lzkn64.o

default: lzkn64

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

lzkn64: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

liblzkn64.a: $(LIB_OBJS)
	ar rcs $@ $^

lib: liblzkn64.a

clean:
	rm -f *.o *.a lzkn64

.PHONY: lib clean