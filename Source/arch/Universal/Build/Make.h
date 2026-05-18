#pragma once
#include <stdlib.h>

#ifndef __MK_BITS
#error "__MK_BITS is not defined. The build process cannot continue"
#endif
#define MkBits str(__MK_BITS)

#ifndef __MK_VERSION
#warning "__MK_VERSION is not defined. Defaulting to "undefined""
#define __MK_VERSION "undefined"
#endif
#define MkVersion str(__MK_VERSION)

#ifndef __MK_EDITION
#warning "__MK_EDITION is not defined. Defaulting to "undefined""
#define __MK_EDITION "undefined"
#endif
#define MkEdition str(__MK_EDITION)

#ifndef __MK_PLATFORM
#warning "__MK_PLATFORM is not defined. Defaulting to "undefined""
#define __MK_PLATFORM "undefined"
#endif
#define MkPlatform str(__MK_PLATFORM)

#ifndef __MK_NAME
#warning "__MK_NAME is not defined. Defaulting to "undefined""
#define __MK_NAME "undefined"
#endif
#define MkName str(__MK_NAME)

#ifndef __MK_LOADER
#warning "__MK_LOADER is not defined. Defaulting to "undefined""
#define __MK_LOADER "undefined"
#endif
#define MkLoader str(__MK_LOADER)