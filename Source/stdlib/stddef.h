#pragma once
#include <stdint.h>
#define NULL 0
#ifdef __32
typedef uint32_t size_t;
#else
typedef uint64_t size_t;
#endif