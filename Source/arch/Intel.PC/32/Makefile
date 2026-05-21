CFLAGS+=-I $(ARCHDIR)/include
include $(wildcard $(ARCHDIR)/include/*/Makefile)
include $(wildcard $(ARCHDIR)/include/Device/*/Makefile)
include $(ARCHDIR)/$(LOADER)/Makefile

KERNEL_ARCH_OBJS+=$(patsubst %.c,%.o,$(wildcard $(ARCHDIR)/*.c))