#include "Keyboard.h"
#include <stdint.h>
#include <stdbool.h>
#include <Device/CPU/Interrupt.h>
#include <Device/IO.h>
#include <Device/Terminal/Console.h>
#include <DAL.h>
#include <Device/CPU/ISRS.h>
#include "Keyboard.h"

DALDevice* KeyboardDevice = &(DALDevice)
{
	.Name = "keyboardctrl",
	.Properties = &(DALProperties) {
		.Bus = DeviceBusISA,
		.Type = DeviceTypeKeyboard
	},
	.Uninitialize = KeyboardUninit,
	.Initialize = KeyboardInit,
	.Command = 0
};

char KeyboardBuffer[1024];
uint8_t KeyboardBufferIndex = 0;
volatile bool HideInput = false;
volatile void* KeyboardEvent[5];


// TODO: Replace placeholder
char CurrentLayout[] = {
    [0x01] = 0, [0x3B] = 0x70, [0x3C] = 0, [0x3D] = 0, [0x3E] = 0, [0x3F] = 0, [0x40] = 0, [0x41] = 0, [0x42] = 0,
    [0x43] = 0, [0x44] = 0, [0x57] = 0, [0x58] = 0, [0x54] = 0, [0x46] = 0,
    [0x29] = '`', [0x02] = '1', [0x03] = '2',  [0x04] = '3', [0x05] = '4', [0x06] = '5', [0x07] = '6', [0x08] = '7',
    [0x09] = '8', [0x0A] = '9', [0x0B] = '0', [0x0C] = '-', [0x0D] = '=', [0x0E] = '\b',
    [0x0F] = '\t', [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r', [0x14] = 't', [0x15] = 'y',
    [0x16] = 'u', [0x17] = 'i', [0x18] = 'o', [0x19] = 'p', [0x1A] = '[', [0x1B] = ']', [0x2B] = '\\',
    [0x3A] = 0, [0x1E] = 'a', [0x1F] = 's', [0x20] = 'd', [0x21] = 'f', [0x22] = 'g', [0x23] = 'h',
    [0x24] = 'j', [0x25] = 'k', [0x26] = 'l', [0x27] = ';', [0x28] = '\'', [0x1C] = '\n',
    [0x2A] = 0, [0x2C] = 'z', [0x2D] = 'x', [0x2E] = 'c', [0x2F] = 'v', [0x30] = 'b', [0x31] = 'n',
    [0x32] = 'm', [0x33] = ',', [0x34] = '.', [0x35] = '/', [0x36] = 0, [0x1D] = 0, [0x38] = 0,
    [0x39] = ' '
};

void ClearKeyboardBuffer() {
    for (uint16_t i = 0; i < sizeof(KeyboardBuffer) / sizeof(KeyboardBuffer[0]); i++) {
        KeyboardBuffer[i] = 0;
    }
    KeyboardBufferIndex = 0;
}

void KeyboardHandler(Registers* Regs)
{
	(void)Regs;
	uint8_t ScanCode = inb(0x60);

	if (!(ScanCode & 0x80))
	{
		KeyboardBuffer[KeyboardBufferIndex++] = CurrentLayout[ScanCode];
		if (ScanCode < sizeof(CurrentLayout) / sizeof(CurrentLayout[0]) && 
			CurrentLayout[ScanCode] != 0)
		{
			if (CurrentLayout[ScanCode] == '\b')
			{
				if (DefaultConsole->X-- == 0)
				{
					DefaultConsole->X = 0;
				}
				DefaultConsole->WriteChar(' ');
			}
			DefaultConsole->WriteChar(CurrentLayout[ScanCode]);
		}
	}
}

void KeyboardInit(DALDevice* Device)
{
	RegisterIRQHandler(1, KeyboardHandler);
	Device->SendKrnMessage(MsgDevReady, Device);
}

void KeyboardUninit(DALDevice* Device)
{
	RegisterIRQHandler(1, 0);
	Device->SendKrnMessage(MsgDevUnloaded, Device);
}
