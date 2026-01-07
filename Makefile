find-command = $(shell which $(1) 2>/dev/null)

BASENAME    = mnsg
VERSION    ?= usa
COMPRESSED  = no

##### Directories #####
BUILD_DIR = build/$(VERSION)
CONFIG_DIR = config/$(VERSION)

BIN_DIRS := $(shell find bin/$(VERSION) -type d 2>/dev/null)
ASM_DIRS := $(shell find asm -type d -not -path "asm/$(VERSION)/nonmatchings*" 2>/dev/null)
SRC_DIRS := $(shell find src -type d 2>/dev/null)

##### Tools #####
ifneq      ($(call find-command,mips-linux-gnu-ld),)
	CROSS := mips-linux-gnu-
else ifneq ($(call find-command,mips64-linux-gnu-ld),)
	CROSS := mips64-linux-gnu-
else ifneq ($(call find-command,mips64-elf-ld),)
	CROSS := mips64-elf-
else
  $(error Unable to detect a suitable MIPS toolchain installed.)
endif

UV ?= uv
PYTHON ?= $(UV) run python
SPLAT ?= $(UV) run splat

CC := tools/ido-5.3/cc

AS := $(CROSS)as
LD := $(CROSS)ld
OBJCOPY := $(CROSS)objcopy
OBJDUMP := $(CROSS)objdump

CHECK_WARNINGS := -Wall -Wextra -Wno-format-security -Wno-unknown-pragmas -Wno-unused-parameter -Wno-unused-variable -Wno-missing-braces -Wno-int-conversion
CC_CHECK := gcc -fno-builtin -fsyntax-only -fsigned-char -std=gnu90 -D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI -D__sgi -DNDEBUG $(CHECK_WARNINGS)

##### Flags #####
INCLUDES := -Iinclude -Ilibultra/include -Ilibultra/include/PR -Isrc -I.

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

TARGET := $(BUILD_DIR)/$(BASENAME)
LD_SCRIPT := .splat/$(VERSION)/$(BASENAME).ld

$(BUILD_DIR)/src/boot/is_debug.c.o:  OPTFLAGS := -O2 -g3
$(BUILD_DIR)/src/boot/audio/seq.c.o: OPTFLAGS := -O2 -g3

EUC_JP_SRCS := \
    asm/usa/data/file_32.rodata.s \
	asm/usa/data/file_44.rodata.s \
	asm/usa/data/file_59.rodata.s \

EUC_JP_OBJS := $(foreach file,$(EUC_JP_SRCS),$(BUILD_DIR)/$(file).o)

FILE_ENCODING = Shift_JIS

$(EUC_JP_OBJS): FILE_ENCODING = EUC-JP

##### Targets #####
default: all

all: $(TARGET).z64
	@sha1sum $(TARGET).z64
ifeq ($(COMPRESSED),yes)
	@sha1sum -c $(CONFIG_DIR)/$(BASENAME).sha1
else
	@sha1sum -c $(CONFIG_DIR)/$(BASENAME).uncompressed.sha1
endif

$(TARGET).z64: $(TARGET).elf
	$(OBJCOPY) -O binary $(OBJCOPYFLAGS) $< $@
ifeq ($(COMPRESSED),yes)
	$(PYTHON) tools/rommy.py compress --input $@ --output $@ --manifest $(CONFIG_DIR)/rommy.yaml --pad --verify
endif

$(TARGET).elf: $(O_FILES)
	$(LD) -T $(LD_SCRIPT) -Map $(TARGET).map -T .splat/$(VERSION)/undefined_syms_auto.ld -T .splat/$(VERSION)/undefined_funcs_auto.ld --no-check-sections --emit-relocs -o $@

nuke:
	rm -rf asm
	rm -rf bin
	rm -rf build
	rm -f *auto.txt
	rm -f *.ld
	rm -f config/japan_0/baserom.decompressed.z64
	rm -f config/usa/baserom.decompressed.z64

clean:
	rm -rf build

setup: baserom.$(VERSION).decompressed.z64
	$(SPLAT) split $(CONFIG_DIR)/splat.yaml

baserom.$(VERSION).decompressed.z64:
	$(PYTHON) tools/rommy.py decompress --input $(CONFIG_DIR)/baserom.z64 --output $(CONFIG_DIR)/baserom.decompressed.z64 --manifest $(CONFIG_DIR)/rommy.yaml --pad

##### Recipes #####
ifndef PERMUTER
$(GLOBAL_ASM_O_FILES): CC := tools/asm-processor/asm-processor --input-enc=utf-8 --output-enc=$(FILE_ENCODING) $(CC) -- $(AS) $(ASFLAGS) --
endif

$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $$(dirname $@)
	@$(CC_CHECK) $(INCLUDES) $<
ifdef PERMUTER
	$(CC) -c $(CFLAGS) $(OPTFLAGS) $(MIPSISA) -o $@ $<
else
	iconv -f UTF-8 -t $(FILE_ENCODING) $< > $@.encoded.c
	$(CC) -c $(CFLAGS) $(OPTFLAGS) $(MIPSISA) -o $@ $@.encoded.c
endif

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $$(dirname $@)
ifdef PERMUTER
	$(AS) $(ASFLAGS) -o $@ $<
else
	iconv -f UTF-8 -t $(FILE_ENCODING) $< > $@.encoded.s
	$(AS) $(ASFLAGS) -o $@ $@.encoded.s
endif

$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $$(dirname $@)
	$(LD) -r -b binary -o $@ $<