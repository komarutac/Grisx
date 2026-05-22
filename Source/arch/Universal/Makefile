CFLAGS+=-I $(Universal)
include $(wildcard arch/Universal/*/Makefile)
KERNEL_ARCH_OBJS+=$(patsubst %.c,%.o,$(wildcard arch/Universal/*.c))