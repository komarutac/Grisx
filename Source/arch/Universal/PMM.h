#pragma once
#include <stddef.h>
#include <stdbool.h>

extern void* pmalloc();
extern void pfree(void* Pointer);
extern bool PMMInit(void* MemoryMap, uint32_t Length);
extern uint32_t FreeMemory;
extern uint32_t UsedMemory;