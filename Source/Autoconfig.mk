ifeq ($(HOSTOS), Darwin)
EDITION=applemac
else
EDITION=base
endif

ifneq ($(shell which clang),)
CC=clang
endif

include Profile/intel.pc.32.base.multiboot.mk

ifeq ($(CC),)
ifneq ($(shell which $(ARCHAKA)-$(OUTPUTFORMAT)-gcc),)
CC=$(ARCHAKA)-$(OUTPUTFORMAT)-gcc
endif
endif

ifneq ($(shell which nasm),)
AS=nasm
else
ifneq ($(shell which yasm),)
AS=yasm
endif
endif