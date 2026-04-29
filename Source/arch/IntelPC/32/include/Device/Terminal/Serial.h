#pragma once
#include <stdbool.h>
#include <stdint.h>

/*
char Layout[] = {
	[0x01] = 0, [0x3B] = 0x70, [0x3C] = 0, [0x3D] = 0, [0x3E] = 0, [0x3F] = 0, [0x40] = 0, [0x41] = 0, [0x42] = 0,
	[0x43] = 0, [0x44] = 0, [0x57] = 0, [0x58] = 0, [0x54] = 0, [0x46] = 0,
	[0x29] = '`', [0x02] = '1', [0x03] = '2',  [0x04] = '3', [0x05] = '4', [0x06] = '5', [0x07] = '6', [0x08] = '7',
	[0x09] = '8', [0x0A] = '9', [0x0B] = '0', [0x0C] = '-', [0x0D] = '=', [0x0E] = '\b',
	[0x0F] = '\t', [0x10] = 'q', [0x11] = 'w', [0x12] = 'e', [0x13] = 'r', [0x14] = 't', [0x15] = 'y',
	[0x16] = 'U', [0x17] = 'I', [0x18] = 'O', [0x19] = 'P', [0x1A] = '[', [0x1B] = ']', [0x2B] = '\\',
};

void Keyboard() {

	while (true) {
		Byte Data = inb(0x60);
		while (Data == 0xFA) {
			Data = inb(0x60);
		}

		for (int i = 0; i < sizeof(Layout) / sizeof(Layout[0]); i++) {
			if (i == Data) {
				WriteFormat("Key: 0x%h '%c'\n", Data, Layout[Data]);
			}
		}
	}
}*/


extern uint8_t SerialWrite(uint8_t Data);
extern uint8_t SerialRead();
extern void SerialWriteByte(uint8_t Data);
extern void SerialWriteString(char* Data);
extern void LoadSerialDebugPointers();