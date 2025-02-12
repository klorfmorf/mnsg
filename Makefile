BASENAME = mnsg
VERSION ?= us

ifeq ($(VERSION), jp)
	FILE_ADDRESS_TABLE_OFFSET = 0x58258
else ifeq ($(VERSION), us)
	FILE_ADDRESS_TABLE_OFFSET = 0x57FD8
else ifeq ($(VERSION), eu)
	FILE_ADDRESS_TABLE_OFFSET = 0x58AE8
endif

##### Directories #####
BUILD_DIR = build/$(VERSION)
CONFIG_DIR = config/$(VERSION)

BIN_DIRS := $(shell find assets/$(VERSION) -type d 2>/dev/null)
ASM_DIRS := $(shell find asm -type d -not -path "asm/$(VERSION)/nonmatchings*" 2>/dev/null)
SRC_DIRS := $(shell find src -type d 2>/dev/null)

##### Tools #####
ifeq ($(shell type mips-linux-gnu-ld >/dev/null 2>/dev/null; echo $$?), 0)
	CROSS := mips-linux-gnu-
else
	$(error Please install or build mips-linux-gnu)
endif

VENV ?= .venv
PYTHON ?= $(VENV)/bin/python3

CC  := tools/ido-5.3/cc

AS := $(CROSS)as
LD := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
OBJDUMP := $(CROSS)objdump

CHECK_WARNINGS := -Wall -Wextra -Wno-format-security -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-int-conversion
CC_CHECK := gcc -fno-builtin -fsyntax-only -fsigned-char -std=gnu90 -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI -D__sgi -DNDEBUG $(CHECK_WARNINGS)

##### Flags #####
INCLUDES := -Iinclude -Iinclude/libultra -Iinclude/libultra/PR -Isrc -I.

MIPSISA  := -mips2
OPTFLAGS := -O2

ASFLAGS := -EB -mtune=vr4300 -march=vr4300 -mabi=32 -Iinclude -I.
CFLAGS  := -G 0 -non_shared -Xfullwarn -Xcpluscomm $(INCLUDES) -Wab,-r4300_mul -woff 649,838,712 -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI -D__sgi -DNDEBUG
OBJCOPYFLAGS := --pad-to=0x2000000 --gap-fill=0x00

##### Files #####
BIN_FILES := $(foreach dir,$(BIN_DIRS),$(wildcard $(dir)/*.bin))
S_FILES   := $(foreach dir,$(ASM_DIRS),$(wildcard $(dir)/*.s))
C_FILES   := $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))

O_FILES := $(foreach file,$(S_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(C_FILES),$(BUILD_DIR)/$(file).o) \
           $(foreach file,$(BIN_FILES),$(BUILD_DIR)/$(file).o)

GLOBAL_ASM_C_FILES := $(shell grep -rl GLOBAL_ASM $(SRC_DIRS) | sort -u)
GLOBAL_ASM_O_FILES := $(foreach file,$(GLOBAL_ASM_C_FILES),$(BUILD_DIR)/$(file).o)

TARGET := $(BUILD_DIR)/$(BASENAME).$(VERSION)
LD_SCRIPT := $(BASENAME).$(VERSION).ld

$(BUILD_DIR)/src/boot/is_debug.c.o: OPTFLAGS := -O2 -g3
$(BUILD_DIR)/src/boot/audio/seq.c.o: OPTFLAGS := -O2 -g3 

##### Targets #####
default: all

all: $(TARGET).z64
	@sha1sum $(TARGET).z64
	@sha1sum -c $(CONFIG_DIR)/$(BASENAME).$(VERSION).sha1

$(TARGET).z64: $(TARGET).elf tools/rommy/rommy tools/n64crc/n64crc
	$(OBJCOPY) -O binary $(OBJCOPYFLAGS) $< $@
	tools/rommy/rommy -i $@ -o $@ -r baserom.$(VERSION).z64 -c -a $(FILE_ADDRESS_TABLE_OFFSET) -p
	tools/n64crc/n64crc $@

$(TARGET).elf: $(LD_SCRIPT) $(O_FILES)
	$(LD) -T $(LD_SCRIPT) -Map $(TARGET).map -T undefined_syms.$(VERSION).txt -T undefined_syms_auto.txt -T undefined_funcs_auto.txt --no-check-sections -o $@

nuke:
	rm -rf build
	rm -rf assets
	rm -rf asm
	rm -f *auto.txt
	rm -f *.ld
	rm -f baserom.jp.decompressed.z64
	rm -f baserom.us.decompressed.z64
	make -C tools clean

clean:
	rm -rf build

setup: baserom.$(VERSION).decompressed.z64
	splat split $(CONFIG_DIR)/$(BASENAME).$(VERSION).yaml

baserom.$(VERSION).decompressed.z64:
	make -C tools
	tools/rommy/rommy -i baserom.$(VERSION).z64 -o baserom.$(VERSION).decompressed.z64 -d -a $(FILE_ADDRESS_TABLE_OFFSET) -p
	tools/n64crc/n64crc baserom.$(VERSION).decompressed.z64

tools/rommy/rommy:
	make -C tools rommy

tools/n64crc/n64crc:
	make -C tools n64crc

##### Recipes #####
ifndef PERMUTER
$(GLOBAL_ASM_O_FILES): CC := $(PYTHON) tools/asm-processor/build.py $(CC) -- $(AS) $(ASFLAGS) --
endif

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $$(dirname $@)
#	@$(CC_CHECK) $(INCLUDES) $<
	$(CC) -c $(CFLAGS) $(OPTFLAGS) $(MIPSISA) -o $@ $<

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $$(dirname $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $$(dirname $@)
	$(LD) -r -b binary -o $@ $<
