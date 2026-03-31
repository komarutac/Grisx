#pragma once
#include <stdint.h>

#define BlockFree 0x0
#define BlockTaken 0x01

struct _GAS
{
  uint8_t AddressSpace;
  uint8_t BitWidth;
  uint8_t BitOffset;
  uint8_t AccessSize;
  uint64_t Address;
}; typedef struct _GAS GAS;

struct _MemoryBlock {
	int Flags;
	size_t Size;
	GAS Address;
	struct _MemoryBlock* Next;
	struct _MemoryBlock* Previous;
}; typedef struct _MemoryBlock MemoryBlock;

void* pmalloc(size_t Size);
void pfree(void* Pointer);