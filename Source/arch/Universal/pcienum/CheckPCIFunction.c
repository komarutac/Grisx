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
	uint8_t HeaderType = PCIReadByte(Bus, Device, Function, 0xC + 2);

	if (VendorID == 0xFFFF)
	{
		return;
	}
	
	ParentDevice->Properties->Class = BaseClass;
	ParentDevice->Properties->SubClass = SubClass;
	ParentDevice->Properties->Vendor = VendorID;
	ParentDevice->Properties->DeviceID = DeviceID;
	PCIApplyName(BaseClass, SubClass, 0, ParentDevice);

	if ((HeaderType & ~(1 << 7)) == 0)
	{
		// TODO: Do something with the BARs
		for (int i = 0x10; i < 0x24; i += 4)
		{
			uint16_t BARLower = PCIReadWord(Bus, Device, Function, i);
			uint16_t BARUpper = PCIReadWord(Bus, Device, Function, i + 2);
			uint32_t BAR = (BARUpper << 8) | BARLower;

			if (BAR == 0)
			{
				continue;
			}

			if (BAR & 1)
			{
				// IO
			}
			else
			{
				// Memory
				unsigned char Type = (BAR & (3 << 1)) >> 1;

				if (Type == 0)
				{
					// 32-Bit
				}
				else if (Type == 2)
				{
					// 64-Bit
				}
			}
		}
	}

	if ((BaseClass == 0x6) && (SubClass == 0x4))
	{
		SecondaryBus = PCIReadByte(Bus, Device, Function, 0x18 + 1);

		DALDevice* SubDevice = allocator(bump, alloc)(sizeof(DALDevice));
		SubDevice->Name = BusName;						
		
		CheckPCIBus(SecondaryBus, SubDevice);
		RegisterDALDeviceChild(ParentDevice, SubDevice, PCIDevice->SendKrnMessage);
	}
}