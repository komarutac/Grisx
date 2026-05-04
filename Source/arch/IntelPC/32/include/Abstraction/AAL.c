#include <DAL.h>
#include <Device/CPU/PIC.h>
#include <Device/CPU/PIT.h>
#include <Device/Terminal/Keyboard.h>
#include <AAL.h>
#include <Device/CPU/IDT.h>
#include <stddef.h>

void ArchInit(DALDevice* Device)
{
	RegisterDALDeviceChild(Device, PICDevice, MessageCallback);
	IDTInstall();
	RegisterDALDeviceChild(Device, KeyboardDevice, MessageCallback);
	RegisterDALDeviceChild(Device, PITDevice, MessageCallback);
	Device->Command(AALEnableInterrupts, NULL, Device);
	Device->SendKrnMessage(MsgDevReady, Device);
}

void* ArchCommand(int Function, void* Arguments, DALDevice* Device) {
    (void)Arguments;
    (void)Device;
    switch (Function)
    {
    case AALDisableInterrupts:
        __asm ("cli");
        break;
    case AALEnableInterrupts:
        __asm ("sti");
        break;
    case AALHalt:
        __asm ("hlt");
        break;
    default:
        return NULL;
    }
}

DALDevice* ArchDevice = &(DALDevice)
{
	.Name = "arch",
	.Properties = &(DALProperties) {
		.Bus = DeviceBusCPU,
		.Type = 0,
	},
	.Uninitialize = 0,
	.Initialize = ArchInit,
	.Command = ArchCommand
};