EDITION=base
ifeq ($(HOSTARCH), x86_64)
include Profile/intel.pc.64.base.uefi.mk
endif
ifeq ($(HOSTARCH), amd64)
include Profile/intel.pc.64.base.uefi.mk
endif
ifeq ($(HOSTARCH), i386)
include Profile/intel.pc.32.base.multiboot.mk
endif
ifeq ($(HOSTARCH), i686)
include Profile/intel.pc.32.base.multiboot.mk
endif
ifeq ($(HOSTARCH), i686-AT386)
include Profile/intel.pc.32.base.multiboot.mk
endif
ifeq ($(HOSTARCH), Power Macintosh)
include Profile/powerpc.of.32.applemac.of.mk
endif
ifeq ($(HOSTARCH), x86)
include Profile/intel.pc.32.base.multiboot.mk
endif
ifeq ($(HOSTOS), Darwin)
EDITION=applemac
endif