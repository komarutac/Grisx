#include <stdint.h>
#include <PCI.h>
#include <Device/IO.h>

uint8_t PCIReadByte(uint8_t Bus, uint8_t Slot, uint8_t Function, uint8_t Offset)
{
	uint32_t Address, Bus32, Slot32, Function32;
	uint8_t Result;
	unsigned long Temp;
	Bus32 = (uint32_t) Bus;
	Slot32 = (uint32_t) Slot;
	Function32 = (uint32_t) Function;
	Address = (uint32_t) (Bus32 << 16) | (Slot32 << 11) | (Function32 << 8) | (Offset & 0xFC) | (uint32_t) 0x80000000;
	outl(0xCF8, Address);
	Temp = inl(0xCFC);
	Result = (Temp >> ((Offset & 3) * 8)) & 0xFF;
	return Result;
}