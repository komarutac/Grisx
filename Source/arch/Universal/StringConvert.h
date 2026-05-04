#pragma once
#include <stdint.h>
extern char SBase20[];
extern char SBase16[];
extern char SBase10[];
extern char SBase2[];
extern unsigned long SBaseGetSafeSize(unsigned long Integer, int Division);
extern void strrev(int i, char* Destination);
extern void SBaseToString(unsigned long Integer, char* Destination, char* Array, int Division);