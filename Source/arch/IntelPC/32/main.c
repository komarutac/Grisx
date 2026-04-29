#include <Device/Terminal/Serial.h>
#include <Device/VGA/ColorTextMode.h>
#include <Device/VGA/Cursor.h>
#include <Device/Terminal/Console.h>
#include <Device/CPU/GDT.h>
#include <Shared/Options.h>
#include <Die.h>
#include <Device/CPU/IDT.h>
#include <Device/CPU/PIC.h>
#include <Device/CPU/PIT.h>
#include <Device/Terminal/Keyboard.h>
#include <Device/FloppyController/Floppy.h>
#include <Device/ISA/PnP/IO.h>
#include <Log.h>
#include <DAL.h>
#include <stddef.h>
#include <Device/PCI/PCI.h>
#include <Device/ACPI/ACPI.h>
#include "main.h"
#include <Device/Memory.h>
#include <AAL.h>
#include <Device/Terminal/Serial.h>
#include <VFS.h>
#include <KernelMain.h>

void SetupTextMode()
{
	VCClear();
	VCLoadConsolePointers();
}

void SetupVideo()
{
	SetupTextMode();
	DebugConsole = NullConsole;
}

void ArchInit(DALDevice* Device)
{
	RegisterDALDeviceChild(ArchDevice, PICDevice, MessageCallback);
	IDTInstall();
	RegisterDALDeviceChild(ArchDevice, KeyboardDevice, MessageCallback);
	RegisterDALDeviceChild(ArchDevice, PITDevice, MessageCallback);
	__asm ("sti");
	Device->SendKrnMessage(MsgDevReady, Device);
}

DALDevice* ArchDevice = &(DALDevice)
{
	.Name = "arch",
	.Bus = DeviceBusCPU,
	.Type = 0,
	.Uninitialize = 0,
	.Initialize = ArchInit,
	.Command = 0
};

void Loader() {
	SetupVideo();
	KernelMain();
}