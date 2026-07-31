#include <main.h>
#include <Device/CPU/GDT.h>
#include "Loader.h"
#include <KernelMain.h>
#include <Abstraction/Console.h>
#include <Build/Linker.h>
#include <Device/CPU/IDT.h>
#include <Device/PMM/Map.h>
#include <Device/CPU/Paging.h>
#include <PMM.h>

MultibootHeader* Multiboot;

void Loader(uint32_t BootloaderMagic, MultibootHeader* Info) {
	(void)BootloaderMagic;
	(void)Info;
	Multiboot = Info;

	DisablePaging();
	IDTInstall();
	GDTInstall();
	SetupVideo();

	printf("Initializing physical memory...\r\n");
	printf("Physical Memory Layout: [");
	PMMInit((void*)Info->MemoryMapAddress, Info->MemoryMapLength);
	printf("Kernel Text: 0x%X-0X%X\r\n", (uint32_t)&StartText, (uint32_t)&EndText);
	printf("Kernel Data: 0x%X-0X%X\r\n", (uint32_t)&StartAllData, (uint32_t)&EndAllData);
	printf("Loading %d module(s)...\r\n", Info->ModuleCount);

	printf("Starting kernel...\r\n");
	KernelMain();
}