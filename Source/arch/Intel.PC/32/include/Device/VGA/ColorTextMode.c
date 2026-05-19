#include "ColorTextMode.h"
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <Device/IO.h>
#include "Cursor.h"

uint8_t VCResWidth = 80;
uint8_t VCResHeight = 25;
uint8_t VCResLeft = 0;
uint8_t VCResTop = 0;
uint16_t* VCTextBuffer0 = (uint16_t*)0xB8000;
uint8_t VCCharLeft = 0;
uint8_t VCCharTop = 0;
uint8_t VCForegrond = 0x7;
uint8_t VCBackground = 0x0;
uint8_t VCTextColor = 0x07;
uint8_t VCLineHeight = 0x01;
uint16_t VCConsoleBuffer[80 * 50];
uint8_t VCIndent = 4;

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

	outb(0x3CE, 4);
	outb(0x3CF, Plane);

	outb(0x3C4, 2);
	outb(0x3C5, PMask);
}

void VCSetFont(uint8_t *Buffer, uint16_t FontHeight)
{
	uint8_t seq2, seq4, gc4, gc5, gc6;
	uint8_t* Pointer = (uint8_t*) 0xB8000;

	outb(0x3C4, 2);
	seq2 = inb(0x3C5);

	outb(0x3C4, 4);
	seq4 = inb(0x3C5);

	outb(0x3C5, 0x04);

	outb(0x3CE, 4);
	gc4 = inb(0x3CF);

	outb(0x3CE, 5);
	gc5 = inb(0x3CF);

	outb(0x3CF, gc5 & ~0x10);

	outb(0x3CE, 6);
	gc6 = inb(0x3CF);

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

	outb(0x3C4, 2);
	outb(0x3C5, seq2);
	outb(0x3C4, 4);
	outb(0x3C5, seq4);
	outb(0x3CE, 4);
	outb(0x3CF, gc4);
	outb(0x3CE, 5);
	outb(0x3CF, gc5);
	outb(0x3CE, 6);
	outb(0x3CF, gc6);
}


uint16_t VCCharEntry(const uint16_t Char, const uint16_t Attribute) {
	return Char | Attribute << 8;
}

int VCGetPixels() {
	return VCResWidth * VCResHeight;
}

uint16_t VCCreateIndex(const uint8_t Top, const uint8_t Left) {
	return (Top * VCResWidth) + Left;
}

void VCScrollDown() {
	for (uint8_t Top = VCResTop; Top < DefaultConsole->Y; Top++) {
		for (uint8_t Left = VCResLeft; Left < VCResWidth; Left++) {
			const uint16_t IndexAbove = VCCreateIndex(Top + 1, Left);
			const uint16_t Index = VCCreateIndex(Top, Left);
			DefaultConsole->TextBuffer[Index] = DefaultConsole->TextBuffer[IndexAbove];
		}
	}

	for (uint8_t Left = VCResLeft; Left < DefaultConsole->Width; Left++) {
		const size_t Index = VCCreateIndex(DefaultConsole->Y, Left);
		DefaultConsole->TextBuffer[Index] = VCCharEntry(' ', VCTextColor);
	}
}

void VCSetForegroundColor(ARGB Color) {
	VCForegrond = Color.Red;
	VCTextColor = VGATextColor(VCBackground, VCForegrond);
}

void VCSetBackgroundColor(ARGB Color) {
	VCBackground = Color.Red;
	VCTextColor = VGATextColor(VCBackground, VCForegrond);
}

void VCNewLine() {
	DefaultConsole->Busy = true;

	if (DefaultConsole->Y++ + 1 == VCResHeight) {
		VCScrollDown();
		DefaultConsole->Y--;
	};

	VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
	DefaultConsole->Busy = false;
}

void VCClear() {
	DefaultConsole->Busy = true;
	for (size_t i = 0; i < VCResWidth * VCResHeight; i++) {
		VCTextBuffer0[i] = VCCharEntry(' ', VCTextColor);
	}
	DefaultConsole->Busy = false;
}

void VCUpdate() {
	DefaultConsole->Busy = 1;
	for (size_t i = 0; i < VCResWidth * VCResHeight; i++) {
		if (DefaultConsole->TextBuffer[i] == VCCharEntry(' ', 0) ||
			VCTextBuffer0[i] == DefaultConsole->TextBuffer[i])
			continue;
		VCTextBuffer0[i] = DefaultConsole->TextBuffer[i];
	}
	DefaultConsole->Busy = 0;
}

void VCAddEntry(uint16_t* Array, uint16_t Entry) {
	const size_t Index = VCCreateIndex(DefaultConsole->Y, DefaultConsole->X);
	if (Array[Index] != Entry) {
		Array[Index] = Entry;
	}
}

void VCWriteCharAt(uint8_t Char, int X, int Y) {
	DefaultConsole->TextBuffer[VCCreateIndex(Y, X)] = VCCharEntry(Char, VCTextColor);
	VCUpdate();
}

void VCWriteChar(uint8_t Char) {
	switch (Char) {
		case '\n':
			VCNewLine();
			return;
		case '\t':
			for (size_t i = 0; i < VCIndent; i++) {
				VCWriteChar(' ');
				VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
			}
			return;
		case '\b':
			VMoveCursor(DefaultConsole->Y, DefaultConsole->X--);
			return;
		case '\r':
			DefaultConsole->X = 0;
			VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
			return;
	}

	VCAddEntry(DefaultConsole->TextBuffer, VCCharEntry(Char, VCTextColor));

	if (DefaultConsole->X++ + 1 == VCResWidth) {
		DefaultConsole->X = 0;
		if (DefaultConsole->Y++ + 1 == VCResHeight) {
			VCScrollDown();
			DefaultConsole->Y--;
		}
	}

	VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
}

void VCWriteString(char* Text)
{
	while (*Text != '\0')
	{
		VCWriteChar(*Text);
		Text++;
	}
	VCUpdate();
}

void VCLoadConsolePointers() {
	DefaultConsole->Busy = 1;
	DefaultConsole->X = 0;
	DefaultConsole->Y = 0;
	DefaultConsole->Width = VCResWidth;
	DefaultConsole->Height = VCResHeight;
	DefaultConsole->Clear = &VCClear;
	DefaultConsole->WriteChar = &VCWriteChar;
	DefaultConsole->WriteString = &VCWriteString;
	DefaultConsole->SetForegroundColor = &VCSetForegroundColor;
	DefaultConsole->SetBackgroundColor = &VCSetBackgroundColor;
	DefaultConsole->WriteCharAt = &VCWriteCharAt;
	DefaultConsole->Busy = 0;
	DefaultConsole->TextBuffer = VCConsoleBuffer;
}