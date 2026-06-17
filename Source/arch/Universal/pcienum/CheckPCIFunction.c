#include <Abstraction/DAL.h>
#include <PCI.h>
#include <stdint.h>
#include <macro.h>
#include <balloc.h>

char* BusName = "bus";

void CheckPCIFunction(uint8_t Bus, uint8_t Device, uint8_t Function, DALDevice* ParentDevice)
{
	uint8_t BaseClass;
	uint8_t SubClass;
	uint8_t SecondaryBus;

	BaseClass = PCIReadByte(Bus, Device, Function, 0x8 + 3);
	SubClass = PCIReadByte(Bus, Device, Function, 0x8 + 2);
	uint16_t VendorID = PCIReadWord(Bus, Device, Function, 0x00);
	uint16_t DeviceID = PCIReadWord(Bus, Device, Function, 0x02);

	if (VendorID == 0xFFFF)
	{
		return;
	}
	
	ParentDevice->Properties->Class = BaseClass;
	ParentDevice->Properties->SubClass = SubClass;
	ParentDevice->Properties->Vendor = VendorID;
	ParentDevice->Properties->DeviceID = DeviceID;
	PCIApplyName(BaseClass, SubClass, 0, ParentDevice);
	
	if ((BaseClass == 0x6) && (SubClass == 0x4))
	{
		SecondaryBus = PCIReadByte(Bus, Device, Function, 0x18 + 1);

		DALDevice* SubDevice = allocator(bump, alloc)(sizeof(DALDevice));
		SubDevice->Name = BusName;
		
		CheckPCIBus(SecondaryBus, SubDevice);
		RegisterDALDeviceChild(ParentDevice, SubDevice, PCIDevice->SendKrnMessage);
	}
}