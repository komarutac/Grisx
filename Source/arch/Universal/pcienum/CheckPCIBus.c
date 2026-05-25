#include <Abstraction/DAL.h>
#include <stdint.h>
#include <PCI.h>
#include <Abstraction/Console.h>

DALDevice* CheckPCIBus(uint8_t Bus, DALDevice* BusDevice)
{
	for (int Device = 0; Device < 32; Device++)
	{
		CheckPCIDevice(Bus, Device, BusDevice);
	}
	return BusDevice;
}
