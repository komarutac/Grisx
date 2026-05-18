#include <VFS.h>
#include <AAL.h>
#include <PCI.h>
#include <Console.h>
#include <Die.h>
#include <PAL.h>

void KernelMain()
{
	VFSSetLoop(VirtualLoop);
	VFSInit(MessageCallback);
	RegisterDALDevice(ArchDevice, MessageCallback);
	RegisterDALDevice(PALDevice, MessageCallback);
	RegisterDALDevice(PCIDevice, MessageCallback);

	if (DALFindFirst(DeviceType(DeviceTypeVideo), DALDevices, true) == 0)
	{
		bool HasFallbackFunction = (bool)PALDevice->Command(DevCMDHasFunction, DevCMDSwitchToFallback, PALDevice);
		if (HasFallbackFunction)
		{
			PALDevice->Command(DevCMDSwitchToFallback, DeviceTypeDisplay, PALDevice);
		}
	}

	DALDevice* FirstStorageCtrl = DALFindFirst(DeviceType(DeviceTypeDiskController), DALDevices, true);

	if (FirstStorageCtrl == 0)
	{
		printf("No device with type DiskController found. Can not complete initialization.\r\n");
		Stop("Device Not Found", 0x1000100);
		for (;;);
	}
}