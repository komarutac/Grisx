PROFILE?=none
ifeq ($(PROFILE), none)
AUTOCONFIG?=true
else
AUTOCONFIG?=false
endif
ifeq ($(AUTOCONFIG), false)
include Profile/$(PROFILE).mk
endif
HOSTOS?=$(shell uname -s)
HOSTARCH?=$(shell uname -m)
ifeq ($(AUTOCONFIG), true)
include Autoconfig.mk
endif
OUTPUTFORMAT?=
OUTPUT?=$(PLATFORM).$(BITS).$(EDITION).$(OUTPUTFORMAT)
NAME?=GRISX
ARCHAKA?=
VERSION?=$(shell date "+%y.%m")
HOST?=
PLATFORM?=
BITS?=
LOADER?=
EDITION?=
CC?=
AS?=
ASFLAGS?=
CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=
INC?=
REQINC?=
Universal=arch/Universal
ARCHDIR=arch/$(PLATFORM)/$(BITS)
CFLAGS:=$(CFLAGS) -gdwarf-4 -D__MK_BITS=$(BITS) -D__MK_PLATFORM=$(PLATFORM) -D__MK_LOADER=$(LOADER) -D__MK_EDITION=$(EDITION) -D__MK_VERSION=$(VERSION) -D__MK_NAME=$(NAME) -ffreestanding -Wall -Wextra -nostdlib
CPPFLAGS:=$(CPPFLAGS)
LDFLAGS:=
LIBS:=$(LIBS) 
REQINC:=$(REQINC) stdlib/Makefile $(Universal)/Makefile $(ARCHDIR)/Makefile
INC:=$(INC)

ifeq ($(CC), clang)
CFLAGS+=-D__clang
endif

-include $(INC)
include $(REQINC)

CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS) 

OBJS=\
$(KERNEL_OBJS) 

LINK_LIST=\
$(LDFLAGS) \
$(OBJS) \
$(LIBS)

ifneq ($(shell which qemu-system-$(ARCHAKA)),)
.PHONY: all clean run
else
.PHONY: all clean
endif
.SUFFIXES: .o .c .S .asm


ifneq ($(shell which qemu-system-$(ARCHAKA)),)
run:
	qemu-system-$(ARCHAKA) -kernel $(OUTPUT)
endif

all: Base.kernel
Base.kernel: $(OBJS) $(ARCHDIR)/$(LOADER)/linker.ld
	$(CC) -T $(ARCHDIR)/$(LOADER)/linker.ld -o $(OUTPUT) $(CFLAGS) $(LINK_LIST)
.c.o:
	$(CC) -MD -c $< -o $@ -std=c11 $(CFLAGS) $(CPPFLAGS)
.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)
.asm.o:
	$(AS) $(ASFLAGS) $< -o $@
clean:
	rm -f $(OUTPUT)
	rm -f $(OBJS)
	rm -f $(OBJS:.o=.d)

-include $(OBJS:.o=.d)