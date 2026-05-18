#pragma once
#include <stdlib.h>

#ifndef __MK_BITS
#define __MK_BITS 0
#endif
#define MkBits str(__MK_BITS)

#ifndef __MK_VERSION
#define __MK_VERSION "undefined"
#endif
#define MkVersion str(__MK_VERSION)

#ifndef __MK_EDITION
#define __MK_EDITION "undefined"
#endif
#define MkEdition str(__MK_EDITION)

#ifndef __MK_PLATFORM
#define __MK_PLATFORM "undefined"
#endif
#define MkPlatform str(__MK_PLATFORM)

#ifndef __MK_NAME
#define __MK_NAME "undefined"
#endif
#define MkName str(__MK_NAME)

#ifndef __MK_LOADER
#define __MK_LOADER "undefined"
#endif
#define MkLoader str(__MK_LOADER)