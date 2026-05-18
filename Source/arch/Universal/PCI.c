#include <DAL.h>
#include <stdint.h>
#include <stddef.h>
#include <PCI.h>
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
	.Properties = &(DALProperties)
    {
		.Bus = DeviceBusCPU,
		.Type = DeviceTypeBus,
	},
	.Uninitialize = PCIUninit,
	.Initialize = PCIInit,
	.Command = PCICommand,
	.Test = PCITest
};

bool PCITest(DALDevice* Device)
{
	bool Result = (bool)Device->Command(DevCMDHasFunction, DevCMDGetDeviceInformation, Device);
	if (!Result)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void PCIApplyName(uint8_t BaseClass, uint8_t SubClass, uint8_t ProgIF, DALDevice* Device)
{
	switch (BaseClass)
	{
	case 0x1:
		Device->Name = Storage;
		Device->Properties->Type = DeviceTypeDiskController;
		break;
	case 0x2:
		Device->Name = Network;
		Device->Properties->Type = DeviceTypeNetworkController;
		break;
	case 0x3:
		Device->Name = Display;
		Device->Properties->Type = DeviceTypeVideoController;
		break;
	case 0x4:
		Device->Name = Multimedia;
		Device->Properties->Type = DeviceTypeMultimediaController;
		break;
	case 0x5:
		Device->Name = Memory;
		Device->Properties->Type = DeviceTypeMemoryController;
		break;
	case 0x6:
		Device->Name = Bridge;
		Device->Properties->Type = DeviceTypeBridge;
		break;
	case 0x7:
		Device->Name = Comm;
		Device->Properties->Type = DeviceTypeCommController;
		break;
	case 0x9:
		Device->Name = Input;
		Device->Properties->Type = DeviceTypeInputController;
		break;
	case 0xC:
		Device->Name = SerialBus;
		Device->Properties->Type = DeviceTypeSerialBusController;
		break;
	case 0xD:
		Device->Name = Wireless;
		Device->Properties->Type = DeviceTypeWirelessController;
		break;
	case 0x10:
		Device->Name = Crypto;
		Device->Properties->Type = DeviceTypeCryptoController;
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
	ParentDevice->Properties->Class = BaseClass;
	ParentDevice->Properties->SubClass = SubClass;
	ParentDevice->Properties->Vendor = VendorID;
	ParentDevice->Properties->DeviceID = DeviceID;
	PCIApplyName(BaseClass, SubClass, 0, ParentDevice);
	
	if ((BaseClass == 0x6) && (SubClass == 0x4))
	{
		SecondaryBus = PCIReadByte(Bus, Device, Function, 0x18 + 1);
		DALDevice* SubDevice = &(DALDevice)
		{
			.Name = BusName,
			.Properties = &(DALProperties)
            {
				.Bus = DeviceBusPCI,
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
		.Properties = &(DALProperties)
        {
			.Bus = DeviceBusPCI,
			.Vendor = VendorID
		}
	};
	
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

DALDevice* CheckPCIBus(uint8_t Bus, DALDevice* BusDevice)
{
	for (int Device = 0; Device < 32; Device++)
	{
		CheckPCIDevice(Bus, Device, BusDevice);
	}
	return BusDevice;
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
			.Properties = &(DALProperties)
            {
				.Bus = DeviceBusPCI,
				.HeaderType = HeaderType
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
				.Properties = &(DALProperties)
                {
					.Bus = DeviceBusPCI,
					.HeaderType = HeaderType
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
	(void)Device;
	switch (Function)
	{
		case DevCMDHasFunction:
			uint8_t Argument = (uint8_t)Arguments;
			switch (Argument)
			{
				default:
					return false;
			}
			break;
	}
	return 0;
}