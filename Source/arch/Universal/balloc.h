#pragma once
#include <stddef.h>
#include <macro.h>

extern char Blocks[2048 * 2];
extern int Offset;

extern void* allocator(bump, alloc)(int Size);
extern void bclear();