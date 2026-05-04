#include <DAL.h>
#include <stdbool.h>
#include <stdint.h>
#include "PCI.h"
#include <Device/IO.h>
#include <stddef.h>
#include <Device/Terminal/Console.h>
char* Storage = "storagectrl";
char* Network = "networkctrl";
char* Display = "displayctrl";
char* Multimedia = "multimediactrl";
char* Memory = "memoryctrl";
char* Bridge = "bridge";
char* Generic = "generic";
char* Comm = "commctrl";
char* Input = "inputctrl";
char* SerialBus = "serialctrl";
char* Wireless = "wirelessctrl";
char* Crypto = "cryptoctrl";
char* BusName = "bus";
char* BusHost = "bushost";

DALDevice* PCIDevice = &(DALDevice)
{
	.Name = "pcienum",
	.Properties = &(DALProperties) {
		.Bus = DeviceBusCPU,
		.Type = DeviceTypeBus,
	},
	.Uninitialize = PCIUninit,
	.Initialize = PCIInit,
	.Command = PCICommand
};

void PCIApplyName(uint8_t BaseClass, DALDevice* Device)
{
	switch (BaseClass)
	{
	case 0x1:
		Device->Name = Storage;
		break;
	case 0x2:
		Device->Name = Network;
		break;
	case 0x3:
		Device->Name = Display;
		break;
	case 0x4:
		Device->Name = Multimedia;
		break;
	case 0x5:
		Device->Name = Memory;
		break;
	case 0x6:
		Device->Name = Bridge;
		break;
	case 0x7:
		Device->Name = Comm;
		break;
	case 0x9:
		Device->Name = Input;
		break;
	case 0xC:
		Device->Name = SerialBus;
		break;
	case 0xD:
		Device->Name = Wireless;
		break;
	case 0x10:
		Device->Name = Crypto;
		break;
	default:
		Device->Name = Generic;
		break;
	}
}

void CheckPCIFunction(uint8_t Bus, uint8_t Device, uint8_t Function, DALDevice* ParentDevice)
{
	uint8_t BaseClass;
	uint8_t SubClass;
	uint8_t SecondaryBus;

	BaseClass = PCIReadByte(Bus, Device, Function, 0x8 + 3);
	SubClass = PCIReadByte(Bus, Device, Function, 0x8 + 2);
	uint16_t VendorID = PCIReadConfig(Bus, Device, Function, 0x00);

	if (VendorID == 0xFFFF)
	{
		return;
	}
	
	uint16_t DeviceID = PCIReadConfig(Bus, Device, Function, 0x02);
	PCIApplyName(BaseClass, ParentDevice);
	
	if ((BaseClass == 0x6) && (SubClass == 0x4))
	{
		SecondaryBus = PCIReadByte(Bus, Device, Function, 0x18 + 1);
		DALDevice* SubDevice = &(DALDevice)
		{
			.Name = BusName,
			.Properties = &(DALProperties) {
				.Bus = DeviceBusPCI
			}
		};
		CheckPCIBus(SecondaryBus, SubDevice);
		RegisterDALDeviceChild(ParentDevice, SubDevice, PCIDevice->SendKrnMessage);
	}
}

DALDevice* CheckPCIDevice(uint8_t Bus, uint8_t Device, DALDevice* BusDevice)
{
	uint8_t Function = 0;
	uint16_t VendorID = PCIReadConfig(Bus, Device, Function, 0);

	if (VendorID == 0xFFFF)
	{
		return NULL;
	}

	DALDevice* SubDevice = &(DALDevice)
	{
		.Name = Generic,
		.Properties = &(DALProperties) {
			.Bus = DeviceBusPCI
		}
	};
	
	CheckPCIFunction(Bus, Device, Function, SubDevice);
	uint8_t HeaderType = PCIReadConfig(Bus, Device, Function, 0xC + 2);
	if ((HeaderType & 0x80) != 0) 
	{
		for (Function = 1; Function < 8; Function++) {
			CheckPCIFunction(Bus, Device, Function, SubDevice);
		}
	}
	RegisterDALDeviceChild(BusDevice, SubDevice, PCIDevice->SendKrnMessage);
	return BusDevice;
}

DALDevice* CheckPCIBus(uint8_t Bus, DALDevice* BusDevice)
{
	for (int Device = 0; Device < 32; Device++)
	{
		CheckPCIDevice(Bus, Device, BusDevice);
	}
	return BusDevice;
}

uint16_t PCIReadConfig(uint8_t Bus, uint8_t Slot, uint8_t Function, uint8_t Offset)
{
	uint32_t Address, Bus32, Slot32, Function32;
	uint16_t Result;
	Bus32 = (uint32_t)Bus;
	Slot32 = (uint32_t)Slot;
	Function32 = (uint32_t)Function;
	Address = (uint32_t)(Bus32 << 16) | (Slot32 << 11) | (Function32 << 8) | 
	(Offset & 0xFC) | ((uint32_t)0x80000000);
	outl(0xCF8, Address);
	Result = (uint32_t)(inl(0xCFC) >> ((Offset & 2) * 8)) & 0xFFFF;
	return Result;
}

uint8_t PCIReadByte(uint8_t Bus, uint8_t Slot, uint8_t Function, uint8_t Offset)
{
	uint32_t Address, Bus32, Slot32, Function32;
	uint8_t Result;
	Bus32 = (uint32_t)Bus;
	Slot32 = (uint32_t)Slot;
	Function32 = (uint32_t)Function;
	Address = (uint32_t)(Bus32 << 16) | (Slot32 << 11) | (Function32 << 8) | 
	(Offset & 0xFC) | ((uint32_t)0x80000000);
	outl(0xCF8, Address);
	Result = (inl(0xCFC) >> ((Offset & 3) * 8)) & 0xFF;
	return Result;
}

void PCIUninit(DALDevice* Device)
{
	Device->SendKrnMessage(MsgDevUnloaded, Device);
	return;
}

void PCIInit(DALDevice* Device)
{
	uint8_t Function, Bus, HeaderType;
	HeaderType = PCIReadConfig(0, 0, 0, 0xC + 2);

	if ((HeaderType & 0x80) == 0)
	{
		DALDevice* BusDevice = &(DALDevice)
		{
			.Name = BusHost,
			.Properties = &(DALProperties) {
				.Bus = DeviceBusPCI
			}
		};
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
			DALDevice* BusDevice = &(DALDevice)
			{
				.Name = BusHost,
				.Properties = &(DALProperties) {
					.Bus = DeviceBusPCI
				}
			};
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

void* PCICommand(int Function, void* Arguments, DALDevice* Device)
{
	(void)Function;
	(void)Arguments;
	(void)Device;
	return 0;
}