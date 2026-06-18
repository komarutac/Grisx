#pragma once
#include <stdint.h>
#define MemoryMapTypeFree 1
#define MemoryMapTypeUsed 2
#define MemoryMapTypeReclaimable 3
#define MemoryMapTypeNVS 4
#define MemoryMapTypeBad 5
#define MemoryMapTypeProgramUsed 6

struct _ElfHeaderTable
{
	uint32_t Number;
	uint32_t Size;
	uint32_t Address;
	uint32_t SectionIndex;
}; typedef struct _ElfHeaderTable ElfHeaderTable;

struct _ModuleTable
{
	uint32_t Start;
	uint32_t End;
	uint32_t Name;
	uint32_t Reserved;
}; typedef struct _ModuleTable ModuleTable;

struct _MemoryMapEntry
{
	uint32_t Size;
	uint32_t Address;
	uint32_t _;
	uint32_t Length;
	uint32_t __;
	uint32_t Type;
} __attribute__((packed)); typedef struct _MemoryMapEntry MemoryMapEntry;

struct _MultibootHeader
{
	uint32_t Flags;
	uint32_t LowerMemory;
	uint32_t UpperMemory;
	uint32_t BootDevice;
	uint32_t CommandLine;
	uint32_t ModuleCount;
	uint32_t ModuleAddress;
	ElfHeaderTable Elf;
	uint32_t MemoryMapLength;
	uint32_t MemoryMapAddress;
}; typedef struct _MultibootHeader MultibootHeader;

extern MultibootHeader* Multiboot;