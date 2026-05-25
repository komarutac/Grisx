#pragma once
#include <stddef.h>

extern char Blocks[2048 * 2];
extern int Offset;

extern void* balloc(int Size);
extern void bclear();