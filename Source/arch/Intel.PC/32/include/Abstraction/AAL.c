#include <Abstraction/DAL.h>
#include <Abstraction/AAL.h>
#include <Device/CPU/IDT.h>
#include <stddef.h>
#include <PPI.h>

void ArchInit(DALDevice* Device)
{
    PPITrace(__FUNCTION__);
	IDTInstall();
	Device->SendKrnMessage(MsgDevReady, Device);
}

void* ArchCommand(char Function, void* Arguments, DALDevice* Device) {
    PPITrace(__FUNCTION__);
    (void)Arguments;
    (void)Device;
    switch (Function)
    {
    case AALDisableInterrupts:
        __asm__ ("cli");
        break;
    case AALEnableInterrupts:
        __asm__ ("sti");
        break;
    case AALHalt:
        __asm__ ("hlt");
        break;
    default:
        break;
    }
    return NULL;
}

DALDevice* ArchDevice = &(DALDevice)
{
	.Name = "arch",
	.Properties = &(DALProperties) {
		.Bus = 0,
		.Type = DeviceTypeArch,
	},
	.Uninitialize = 0,
	.Initialize = ArchInit,
	.Command = ArchCommand
};