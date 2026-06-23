#pragma once
#include <stdint.h>
#define MemoryMapTypeFree 1
#define MemoryMapTypeUsed 2
#define MemoryMapTypeReclaimable 3
#define MemoryMapTypeNVS 4
#define MemoryMapTypeBad 5
#define MemoryMapTypeProgramUsed 6

struct _MemoryMapEntry
{
	uint32_t Size;
	uint32_t Address;
	uint32_t PMMFree; 
	uint32_t Length;
	uint32_t PMMFlags;
	uint32_t Type;
} __attribute__((packed)); typedef struct _MemoryMapEntry MemoryMapEntry;

extern MemoryMapEntry* MemoryMapTable;
extern uint32_t MemoryMapTableLength;