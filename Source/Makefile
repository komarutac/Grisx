HOST?=i686-elf
PLATFORM?=IntelPC
BITS?=32
LOADER?=multiboot
EDITION?=base

CC=$(HOST)-gcc
QEMU=qemu-system-x86_64
QEMUFlags=-kernel $(PLATFORM)-$(BITS)_$(EDITION).elf -serial stdio

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=

DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include

Universal=arch/Universal
ARCHDIR=arch/$(PLATFORM)/$(BITS)

CFLAGS:=$(CFLAGS) -ffreestanding -O2 -Wall -Wextra -I $(ARCHDIR)/include -I $(Universal) -nostdlib -lgcc
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=
LIBS:=$(LIBS)

include $(ARCHDIR)/make.config

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS)

OBJS=\
$(KERNEL_OBJS) \

LINK_LIST=\
$(LDFLAGS) \
$(KERNEL_OBJS) \
$(LIBS) \

.PHONY: all clean
.SUFFIXES: .o .c .S .asm

all: Base.kernel

run:
	$(QEMU) $(QEMUFlags)

Base.kernel: $(OBJS) $(ARCHDIR)/$(LOADER)/linker.ld
	$(CC) -T $(ARCHDIR)/$(LOADER)/linker.ld -o $(PLATFORM)-$(BITS)_$(EDITION).elf $(CFLAGS) $(LINK_LIST)

$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o kernel/arch/i386/switch.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@

.c.o:
	$(CC) -MD -c $< -o $@ -std=c11 $(CFLAGS) $(CPPFLAGS)

.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
	
.asm.o:
	nasm -f elf$(BITS) $< -o $@

clean:
	rm -f $(PLATFORM)-$(BITS)_$(EDITION).elf
	rm -f $(OBJS) *.o */*.o */*/*.o */*/*/*/.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d */*/*/*/.d

-include $(OBJS:.o=.d)
