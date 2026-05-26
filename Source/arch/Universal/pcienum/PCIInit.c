#include <Abstraction/DAL.h>
#include <PCI.h>
#include <stdint.h>
#include <stddef.h>
#include <balloc.h>

void PCIInit(DALDevice* Device)
{
	uint8_t Function, Bus, HeaderType;
	HeaderType = PCIReadConfig(0, 0, 0, 0xC + 2);

	if ((HeaderType & 0x80) == 0)
	{
		DALDevice* BusDevice = allocator(bump, alloc)(sizeof(DALDevice));
		BusDevice->Name = BusHost;

		CheckPCIBus(0, BusDevice);
		if (BusDevice != NULL)
		{
			RegisterDALDeviceChild(Device, BusDevice, Device->SendKrnMessage);
			Device->SendKrnMessage(MsgDevReady, Device);
			Device->SendKrnMessage(MsgDevPollNeeded, Device);
		}
	}
	else
	{
		for (Function = 0; Function < 8; Function++)
		{
			if (PCIReadConfig(Bus, 0, Function, 0) == 0xFFFF)
			{
				break;
			}
			Bus = Function;

			DALDevice* BusDevice = allocator(bump, alloc)(sizeof(DALDevice));
			BusDevice->Name = BusHost;

			CheckPCIBus(Bus, BusDevice);
			if (BusDevice != NULL)
			{
				RegisterDALDeviceChild(Device, BusDevice, Device->SendKrnMessage);
				Device->SendKrnMessage(MsgDevPollNeeded, Device);
			}
		}
		Device->SendKrnMessage(MsgDevReady, Device);
	}
}