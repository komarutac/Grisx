#pragma once
#define ___stdlib_str(A) #A
#define str(A) ___stdlib_str(A)
#include <stddef.h>

extern void* malloc(size_t Size);
extern void* realloc(void* Pointer, size_t Size);
extern void calloc(size_t Length, size_t Size);
extern void free(void* Pointer);