#include <Abstraction/VFS.h>
#include <Abstraction/AAL.h>
#include <PCI.h>
#include <Abstraction/Console.h>
#include <Die.h>
#include <Abstraction/PAL.h>

void KernelMain()
{
	VFSSetLoop(VirtualLoop);
	VFSInit(MessageCallback);
	RegisterDALDevice(ArchDevice, MessageCallback);
	RegisterDALDevice(PALDevice, MessageCallback);
	RegisterDALDevice(PCIDevice, MessageCallback);

	DALDevice* FirstStorageCtrl = DALFindFirst(DeviceType(DeviceTypeDiskController), DALDevices, true);

	if (FirstStorageCtrl == 0)
	{
		printf("No device with type DiskController found. Can not complete initialization.\r\n");
		Stop("Device Not Found", 0x1000100);
		for (;;);
	}
}