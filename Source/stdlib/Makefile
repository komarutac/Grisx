CFLAGS+=-I stdlib
include $(wildcard stdlib/*/Makefile)
KERNEL_ARCH_OBJS+=$(patsubst %.c,%.o,$(wildcard stdlib/*.c))