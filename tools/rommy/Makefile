# Makefile for rommy

CC := gcc
CFLAGS := -Wall -Wextra -g

# Uncomment the following lines if you want to use clang instead of gcc
# CC := clang
# CFLAGS := -Wall -Wextra -O2

OBJS = rommy.o main.o

default: rommy

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

../lzkn64/liblzkn64.a:
	$(MAKE) -C ../lzkn64 lib

rommy: $(OBJS) ../lzkn64/liblzkn64.a
	$(CC) -o $@ $^ $(CFLAGS) -L../lzkn64 -llzkn64

clean:
	rm -f *.o *.a rommy

.PHONY: clean