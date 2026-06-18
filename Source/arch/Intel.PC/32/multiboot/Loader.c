#include <main.h>
#include <Device/CPU/GDT.h>
#include "Loader.h"
#include <KernelMain.h>
#include <Abstraction/Console.h>

MultibootHeader* Multiboot;

void HandleModule(ModuleTable* Module)
{
	printf("Loading module %s...\r\n", Module->Name);
}

void Loader(uint32_t BootloaderMagic, MultibootHeader* Info) {
	(void)BootloaderMagic;
	(void)Info;
	Multiboot = Info;

	GDTInstall();
	SetupVideo();

	uint32_t FreeMemory = 0;
	uint32_t BadMemory = 0;
	uint32_t ReclaimableMemory = 0;
	uint32_t UsedMemory = 0;
	uint32_t Entries = 0;

	for (uint32_t i = Info->MemoryMapAddress; i < Info->MemoryMapAddress + Info->MemoryMapLength; i += 4)
	{
		uint32_t Byte = *(uint32_t*)i;

		if (Byte == 0x14)
		{
			MemoryMapEntry* MemMap = (MemoryMapEntry*)i;

			if (MemMap == 0)
			{
				continue;
			}

			if (MemMap->Address == 0 && MemMap->Length == 0)
			{
				continue;
			}

			if (MemMap->Type == MemoryMapTypeFree)
			{
				FreeMemory += MemMap->Length;
			}

			if (MemMap->Type == MemoryMapTypeBad)
			{
				BadMemory += MemMap->Length;
			}

			if (MemMap->Type == MemoryMapTypeReclaimable)
			{
				ReclaimableMemory += MemMap->Length;
			}

			if (MemMap->Type == MemoryMapTypeUsed)
			{
				UsedMemory += MemMap->Length;
			}

			Entries++;
			i += sizeof(MemoryMapEntry) - 4;
		}
	}

	printf("Free physical memory right now: %d kbytes\r\n", FreeMemory / 1024);
	printf("Bad physical memory right now: %d kbytes\r\n", BadMemory / 1024);
	printf("Reclaimable physical memory right now: %d kbytes\r\n", ReclaimableMemory / 1024);
	printf("Used physical memory right now: %d kbytes\r\n", UsedMemory / 1024);
	printf("Physical memory entries right now: %d\r\n", Entries);
	printf("Loading %d module(s)...\r\n", Info->ModuleCount);

	uint32_t Address = Info->ModuleAddress;
	ModuleTable* Module = (ModuleTable*)Address;

	for (uint32_t i = 0; i < Info->ModuleCount; i++)
	{
		HandleModule(Module);
		Module = (ModuleTable*)(Address + Module->End);
	}

	printf("Starting kernel...");
	KernelMain();
}