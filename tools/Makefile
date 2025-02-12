SUB_DIRS := n64crc lzkn64 rommy

.PHONY: all clean

all:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	@for dir in $(SUB_DIRS); do \
		$(MAKE) -C $$dir clean; \
	done