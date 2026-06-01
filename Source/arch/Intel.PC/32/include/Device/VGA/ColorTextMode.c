#include <vgatext.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <Device/IO.h>
#include <Abstraction/Console.h>
#include "Cursor.h"

uint16_t* VCTextBuffer0 = (uint16_t*)0xB8000;

void VCWriteRegister(uint16_t Port, uint8_t Register, uint8_t Value) {
	outb(Port, Register);
	outb(Port + 1, Value);
}

uint8_t VCReadRegister(uint16_t Port, uint8_t Register) {
	uint8_t Temp;
	outb(Port, Register);
	Temp = inb(Port + 1);
	return Temp;
}

void VCSetPlane(unsigned Plane)
{
	unsigned char PMask;

	Plane &= 3;
	PMask = 1 << Plane;

	VCWriteRegister(0x3CE, 4, Plane);
	VCWriteRegister(0x3C4, 2, PMask);
}

void VCSetFont(uint8_t *Buffer, uint16_t FontHeight)
{
	uint8_t seq2, seq4, gc4, gc5, gc6;
	uint8_t* Pointer = (uint8_t*)0xB8000;

	seq2 = VCReadRegister(0x3C4, 2);
	seq4 = VCReadRegister(0x3C4, 4);

	outb(0x3C5, 0x04);

	gc4 = VCReadRegister(0x3CE, 4);
	gc5 = VCReadRegister(0x3CE, 5);

	outb(0x3CF, gc5 & ~0x10);

	gc6 = VCReadRegister(0x3CE, 6);

	outb(0x3CF, gc6 & ~0x02);

	VCSetPlane(2);

	for (size_t i = 0; i < 256; i++) {
		for (size_t j = 0; j < 32; j++) {
			Pointer[32 * i + j] = 0;
		}
	}

	for (size_t i = 0; i < 256; i++) {
		for (size_t j = 0; j < FontHeight; j++) {
			Pointer[32 * i + j] = Buffer[FontHeight * i + j];
		}
	}

	VCWriteRegister(0x3C4, 2, seq2);
	VCWriteRegister(0x3C4, 4, seq4);
	VCWriteRegister(0x3CE, 4, gc4);
	VCWriteRegister(0x3CE, 5, gc5);
	VCWriteRegister(0x3CE, 6, gc6);
}

void VCUpdate() {
	DefaultConsole->Status |= 0b0001; // Set busy bit
	for (size_t i = 0; i < VCResWidth * VCResHeight; i++) {
		if (DefaultConsole->TextBuffer[i] == VCCharEntry(' ', 0) ||
			VCTextBuffer0[i] == DefaultConsole->TextBuffer[i])
			continue;
		VCTextBuffer0[i] = DefaultConsole->TextBuffer[i];
	}
	DefaultConsole->Status &= ~0b0001; // Clear busy bit
}