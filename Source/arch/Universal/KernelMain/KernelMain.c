#include <KernelMain.h>
#include <Abstraction/DAL.h>
#include <ACPI/ACPI.h>

void KernelMain()
{
	InitVFS();
	RegisterDALDevice(ACPISystem, MessageCallback);
	InitPlatformDevices();
	InitPCIEnum();
	for (;;);
}