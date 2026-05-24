PLATFORM?=Intel.PC
LOADER?=multiboot
EDITION?=base
BITS?=32
OUTPUTFORMAT?=elf
ASFLAGS?=-f elf$(BITS)
ARCHAKA=i386

ifeq ($(CC), clang)
CFLAGS+=-target i386-elf
endif