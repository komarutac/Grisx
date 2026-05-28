#include "Serial.h"
#include <stdint.h>
#include <Device/IO.h>
#include <Abstraction/Console.h>

uint16_t* SerialAddress = (uint16_t*)0x400;
int SerialRegister = 0;

void SerialLoadConsole()
{
	DefaultConsole->Busy = 1;
	DefaultConsole->X = 0;
	DefaultConsole->Y = 0;
	DefaultConsole->WriteChar = &SerialWriteByte;
	DefaultConsole->WriteString = &SerialWriteString;
	DefaultConsole->Busy = 0;
}

uint8_t SerialWrite(uint8_t Data)
{
	outb(*SerialAddress + SerialRegister, Data);
	return Data;
}

uint8_t SerialRead()
{
	return inb(*SerialAddress + SerialRegister);
}

void SerialWriteByte(uint8_t Data)
{
	SerialRegister = 0;
	SerialWrite(Data);
}

void SerialWriteString(char* Data)
{
	while (*Data != '\0')
	{
		SerialWriteByte(*Data);
		Data++;
	}
}