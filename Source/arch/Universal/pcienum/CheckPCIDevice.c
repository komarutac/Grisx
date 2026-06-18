#include <Abstraction/DAL.h>
#include <PCI.h>
#include <stdint.h>
#include <stddef.h>
#include <macro.h>
#include <balloc.h>

DALDevice* CheckPCIDevice(uint8_t Bus, uint8_t Device, DALDevice* BusDevice)
{
	uint8_t Function = 0;
	uint16_t VendorID = PCIReadWord(Bus, Device, Function, 0);

	if (VendorID == 0xFFFF)
	{
		return NULL;
	}

	DALDevice* SubDevice = allocator(bump, alloc)(sizeof(DALDevice));
	SubDevice->Name = Generic;
	
	CheckPCIFunction(Bus, Device, Function, SubDevice);
	uint8_t HeaderType = PCIReadByte(Bus, Device, Function, 0xC + 2);
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