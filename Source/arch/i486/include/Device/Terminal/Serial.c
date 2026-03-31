#include "Serial.h"
#include <stdint.h>
#include <Device/IO.h>
#include "Console.h"

uint16_t* SerialAddress = (uint16_t*)0x400;
int SerialRegister = 0;

uint8_t SerialWrite(uint8_t Data) {
	outb(*SerialAddress + SerialRegister, Data);
	return Data;
}
uint8_t SerialRead() {
	return inb(*SerialAddress + SerialRegister);
}

void SerialWriteByte(uint8_t Data) {
	SerialRegister = 0;
	SerialWrite(Data);
}

void SerialWriteString(char* Data) {
	while (*Data != '\0') {
		SerialWriteByte(*Data);
		Data++;
	}
}

void LoadSerialDebugPointers() {
	ConFormatTo(DefaultConsole, "Initializing serial...\r");
	if (*SerialAddress == 0) {
		ConFormatTo(DefaultConsole, "Initializing serial... No serial\n");
		return;
	}
	DebugConsole->Busy = 1;
	DebugConsole->X = 0;
	DebugConsole->Y = 0;
	DebugConsole->WriteChar = &SerialWriteByte;
	DebugConsole->WriteString = &SerialWriteString;
	DebugConsole->WriteLine = &SerialWriteString;
	DebugConsole->Busy = 0;
	ConFormatTo(DefaultConsole, "Initializing serial... Ok\n");
}