#include <Abstraction/PAL.h>
#include <Abstraction/DAL.h>
#include <stdint.h>
#include <stddef.h>
#include <Device/CPU/PIC.h>
#include <Device/CPU/PIT.h>
#include <Device/Terminal/Keyboard.h>
#include <Abstraction/AAL.h>
#include <stddef.h>
#include <Device/CPU/ISRS.h>

void PlatformInit(DALDevice* Device)
{
	ISRSInstall();
	RegisterDALDeviceChild(Device, PICDevice, MessageCallback);
	RegisterDALDeviceChild(Device, KeyboardDevice, MessageCallback);
	RegisterDALDeviceChild(Device, PITDevice, MessageCallback);
	Device->Command(AALEnableInterrupts, NULL, Device);
	Device->SendKrnMessage(MsgDevReady, Device);
}

void* PlatformCommand(char Function, void* Arguments, DALDevice* Device)
{
	(void)Device;
	(void)Arguments;
	(void)Device;
	
	switch (Function)
	{
	case DevCMDHasFunction:
		break;
	default:
		break;
	}

	return NULL;
}

DALDevice* PALDevice = &(DALDevice)
{
	.Name = "platform",
	.Properties = &(DALProperties) {
		.Bus = 0,
		.Type = DeviceTypePlatform,
	},
	.Uninitialize = 0,
	.Initialize = PlatformInit,
	.Command = PlatformCommand
};