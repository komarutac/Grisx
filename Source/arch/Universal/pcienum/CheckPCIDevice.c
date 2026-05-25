#include <Abstraction/DAL.h>
#include <PCI.h>
#include <stdint.h>
#include <stddef.h>

DALDevice* CheckPCIDevice(uint8_t Bus, uint8_t Device, DALDevice* BusDevice)
{
	uint8_t Function = 0;
	uint16_t VendorID = PCIReadConfig(Bus, Device, Function, 0);

	if (VendorID == 0xFFFF)
	{
		return NULL;
	}

	DALDevice* SubDevice = (DALDevice*)balloc(sizeof(DALDevice));
	SubDevice->Name = Generic;
	
	CheckPCIFunction(Bus, Device, Function, SubDevice);
	uint8_t HeaderType = PCIReadConfig(Bus, Device, Function, 0xC + 2);
	SubDevice->Properties->HeaderType = HeaderType;
	if ((HeaderType & 0x80) != 0) 
	{
		for (Function = 1; Function < 8; Function++)
        {
			CheckPCIFunction(Bus, Device, Function, SubDevice);
		}
	}
	RegisterDALDeviceChild(BusDevice, SubDevice, PCIDevice->SendKrnMessage);
	return BusDevice;
}