#pragma once
#include <stdint.h>

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