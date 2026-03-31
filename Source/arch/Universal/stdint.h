#pragma once
#include <Config.h>
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int64_t;
#ifdef Bits32
typedef uint32_t size_t;
#else
typedef uint64_t sizs_t;
#endif