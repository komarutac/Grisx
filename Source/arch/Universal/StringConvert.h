#pragma once
#include <stdint.h>
#include <stddef.h>

extern char SBase16[];
extern size_t GetSizeForBase(int Integer, int Division);
extern void strrev(int i, char* Destination);
extern void IntegerToASCII(unsigned long Integer, char* Destination, char* Array, int Division);