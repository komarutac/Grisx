#include <Abstraction/VFS.h>
#include <Abstraction/AAL.h>
#include <PCI.h>
#include <Abstraction/Console.h>
#include <Die.h>
#include <Abstraction/PAL.h>

void InitVFS()
{
	VFSSetLoop(VirtualLoop);
	VFSInit(MessageCallback);
}

void InitPlatformDevices()
{
	RegisterDALDevice(ArchDevice, MessageCallback);
	RegisterDALDevice(PALDevice, MessageCallback);
}

void InitPCIEnum()
{
	RegisterDALDevice(PCIDevice, MessageCallback);
}

DALDevice* FindDiskCtrl()
{
	DALDevice* FirstStorageCtrl = DALFindFirst(DeviceType(DeviceTypeDiskController), DALDevices, true);

	if (FirstStorageCtrl == 0)
	{
		printf("No device with type DiskController found. Can not complete initialization.\r\n");
		Stop("Device Not Found", 0x1000100);
		for (;;);
	}

	return FirstStorageCtrl;
}

void KernelMain()
{
	InitVFS();
	InitPlatformDevices();
	InitPCIEnum();
	FindDiskCtrl();
}