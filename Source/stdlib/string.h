#pragma once
#include "stdint.h"
#include "stddef.h"
extern size_t strlen(char* String);
extern int strcmp(char* A, char* B);
extern void* memset(void* Pointer, size_t Value, size_t Size);
extern int memcmp(const void* APointer, const void* BPointer, size_t Length);