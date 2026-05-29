#include <main.h>
#include <Device/CPU/GDT.h>
#include "Loader.h"

void Loader(uint32_t BootloaderMagic, LoaderInfo* Info) {
	GDTInstall();
	SetupVideo();
	KernelMain();
}