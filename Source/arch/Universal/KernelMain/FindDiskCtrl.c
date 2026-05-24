#include <PCI.h>
#include <Abstraction/Console.h>
#include <Abstraction/DAL.h>
#include <Die.h>

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