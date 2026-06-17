#include <main.h>
#include <Device/CPU/GDT.h>
#include "Loader.h"
#include <KernelMain.h>
#include <Abstraction/Console.h>

void HandleModule(ModuleTable* Module)
{
	printf("Loading module %s...\r\n", Module->Name);
}

void Loader(uint32_t BootloaderMagic, MultibootHeader* Info) {
	(void)BootloaderMagic;
	(void)Info;

	GDTInstall();
	SetupVideo();

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