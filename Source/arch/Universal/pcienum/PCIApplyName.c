#include <Abstraction/DAL.h>
#include <stdint.h>
#include <PCI.h>

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