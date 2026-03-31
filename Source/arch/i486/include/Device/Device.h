#ifndef C_DEVICE_HEADER
#define C_DEVICE_HEADER
#include <Shared/int.h>

DeviceStruct* Devices = {
	{
		.Name = "PS/2 Keyboard",
		.IRQ = 2,
		.Status = DeviceStatusOK,
		.Type = DeviceTypeKeyboard
	}
};
#endif