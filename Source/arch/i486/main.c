#include <Device/Terminal/Serial.h>
#include <Device/VGA/ColorTextMode.h>
#include <Device/VGA/Cursor.h>
#include <Device/Terminal/Console.h>
#include <Device/CPU/GDT.h>
#include <Shared/Options.h>
#include <Shared/Die.h>
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
#include <Prototypes/File.h>
#include <AAL.h>
#include <Device/Terminal/Serial.h>

int CorruptedConfiguration = 0;

// TODO: Move VerifyConfig, SetupTextMode, SetupVideo, ShutdownDevices, and MessageCallback to their own header files.

void VerifyConfig() {
	if (CorruptedConfiguration) {
		ConFormatTo(DefaultConsole, "Warning: Boot contract violation.\n");
		
		*OPSign = 0xFF;
		*OPTextMode = 0x00;
		*OPRootDC = 0x00;
		*OPRootDN = 0x00;
		*OPDebugMode = 0x01;
		*OPTextBuffer = 0x00;
		*OPSerialAddr = 0x00;
		*OPUseCPUID = 0x00;
	}

	if (*OPDebugMode)
		DebugMode = 1;
}

void SetupTextMode() {
	VCClear();
	VCLoadConsolePointers();

	// Set 8x8 font.
	//VCLoadCommandQueue();
	//VCExecuteCommandQueue();
	//VCSetFont(VCFont8x8, 8);
	//VEnableCursor(0x00, 0x07);
}

void SetupVideo() {
	//CorruptedConfiguration = *OPSign == 0xFF ? 0 : 1;
	//if ((!CorruptedConfiguration && *(DWord*)0x7C10 == 0) /* EGA Compatible */ ||
	//	CorruptedConfiguration) {
	SetupTextMode();
	//LoadSerialDebugPointers();
	DebugConsole = NullConsole;
	//} else if (!CorruptedConfiguration && *(DWord*)0x7C10 == 1 /* VBE */) {
		// TODO: Do VBE things here.
	//}
}

void UninitializeDevices(DALDevice* Devices[]) {
	for (size_t i = 1; i < sizeof(DALDevice) / sizeof(Devices[0]); i++) {
		if (Devices[i] == NULL)
			break;
		DALDevice* Device = Devices[i];
		ConFormatTo(DefaultConsole, "Stopping device %d...\r", i);
		if (Device->Type == DeviceTypePowerManagement) {
			ConFormatTo(DefaultConsole, "Stopping device %d... Skip\n", i);
			continue;
		}
		if (Device->ChildrenCount != 0)
			UninitializeDevices(Device->Children);
		if (Device->Uninitialize)
			Device->Uninitialize(Device);
		Devices[i] = NULL;
	}  
}

void ShutdownDevices() {
	DALDevice* PMDevice = NULL;
	
	ConFormatTo(DefaultConsole, "Looking for power management device...\r");
	
	for (size_t i = 1; i < sizeof(DALDevice) / sizeof(DALDevices[0]); i++) {
		if (DALDevices[i] == NULL)
			break;
		DALDevice* Device = DALDevices[i];
		if (Device->Type == DeviceTypePowerManagement) {
			if (Device->Command != NULL) {
				ConFormatTo(DefaultConsole, "Looking for power management device... Device %d\n", i);
				PMDevice = Device;
			}
		}
	}
	if (PMDevice == NULL) {
		ConFormatTo(DefaultConsole, "Looking for power management device... Not found\n");
	}
	
	ConFormatTo(DefaultConsole, "Stopping devices...\n");
	UninitializeDevices(DALDevices);
	
	ConFormatTo(DefaultConsole, "Shutdown complete.\n");
	
	if (PMDevice != NULL) {
		if (PMDevice->Command != NULL)
			PMDevice->Command(DevCMDPowerShutdown, NULL, PMDevice);
	}
}

int MessageCallback(int Message, DALDevice* Device) {
	if (Message == MsgDevReady) 
		ConFormatTo(DefaultConsole, "Device %s (Type %d, Bus Type %d) ready.\n", Device->Name, Device->Type, Device->Bus);
		
	if (Message == MsgDevUnloaded) 
		ConFormatTo(DefaultConsole, "Device %s (Type %d, Bus Type %d) stopped.\n", Device->Name, Device->Type, Device->Bus);
	
	if (Message == MsgDevError) 
		ConFormatTo(DefaultConsole, "Device %s (Type %d, Bus Type %d) reported an error.\n", Device->Name, Device->Type, Device->Bus);
	
	if (Message == MsgKrnShutdown) {
		ConFormatTo(DefaultConsole, "Device %s (Type %d, Bus Type %d) is requesting system shutdown.\n", Device->Name, Device->Type, Device->Bus);
		ShutdownDevices();
	}
	
	return 0;
}


void ArchInit(DALDevice* Device) {
	ConFormatTo(DefaultConsole, "Initializing PIC...\n");
	RegisterDALDevice(PICDevice, MessageCallback);
	ConFormatTo(DefaultConsole, "Initializing IDT...\n");
	IDTInstall();
	ConFormatTo(DefaultConsole, "Initializing Keyboard...\n");
	RegisterDALDevice(KeyboardDevice, MessageCallback);
	ConFormatTo(DefaultConsole, "Initializing PIT...\n");
	RegisterDALDevice(PITDevice, MessageCallback);
	ConFormatTo(DefaultConsole, "Verifying IDT...\r");
	for (int i = 0; i < 255; i++) {
		if (IDT[i].Flags != 0 && IDT[i].BaseLow == 0) {
			ConFormatTo(DefaultConsole, "Verifying IDT... Bad\n");
			Device->SendKrnMessage(MsgDevError, Device);
			return;
		}
	}
	ConFormatTo(DefaultConsole, "Verifying IDT... Ok\n");
	__asm ("sti");
	Device->SendKrnMessage(MsgDevReady, Device);
}

DALDevice* ArchDevice = &(DALDevice){
	.Name = "Architecture Abstraction Layer",
	.Bus = DeviceBusCPU,
	.Type = 0,
	.Uninitialize = 0,
	.Initialize = ArchInit,
	.Command = 0
};
bool LittleEndian;

void KernelMain() {
	GDTInstall();
	SetupVideo();
	ConFormatTo(DefaultConsole, "Compiler Version: %s\nPreprocessor Timestamp: %s %s\nTarget Architecture: x86\n", __VERSION__, __DATE__, __TIME__);
	ConFormatTo(DefaultConsole, "Kernel Version: %s v%d\n", KernelName, KernelVersion);
	//ConFormatTo(DefaultConsole, "Copyright (c) 2026 komarutac\nUses a tutorial from Brandon Friesen: http://www.osdever.net/bkerndev/Docs/title.htm\nUses information from http://wiki.osdev.org, 3dfx Interactive, Inc., ACPI SIG, PCI-SIG (http://pcisig.com), Intel Corporation, Advanced Micro Devices, Inc., Internet Engineering Task Force, System Management Interface Forum (SMIF), Inc., and UEFI Forum, Inc. (http://uefi.org). Theses groups and companies are not related nor do they endorse or approve this project.\n");
	ConFormatTo(DefaultConsole, "Initializing kernel...\nTesting debug console...\r");
	DebugPrint("Initializing kernel...\n");
	ConFormatTo(DefaultConsole, "Testing debug console... Ok\n");
	RegisterDALDevice(ArchDevice, MessageCallback);
	RegisterDALDevice(ACPISystem, MessageCallback);
	RegisterDALDevice(PCIDevice, MessageCallback);
	//PnpWake(PnPInitiationKey);
	
	DebugPrint("Root filesystem not found.\n");
	ConFormatTo(DefaultConsole, "Unable to find root filesystem.\nShutting down...\n");
	ShutdownDevices();
	for (;;); // Don't return.
}