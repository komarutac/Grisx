#include <VFS.h>
#include <AAL.h>
#include <Device/PCI/PCI.h>
#include <Device/Terminal/Console.h>
#include <Die.h>

void NoStorageDevice()
{
	Alert("no storage device found", "kernel");
}

void IntializationFailure()
{
	Alert("could not complete intialization", "kernel");
}

void KernelMain()
{
	VFSSetLoop(VirtualLoop);
	VFSInit(MessageCallback);
	RegisterDALDevice(ArchDevice, MessageCallback);
	RegisterDALDevice(PCIDevice, MessageCallback);
	if (DALFindFirst((DALProperties) {
		.Type = DeviceTypeDiskController
	}, DALDevices, true) == 0)
	{
		NoStorageDevice();
		IntializationFailure();
		return;
	}
	IntializationFailure();
}
