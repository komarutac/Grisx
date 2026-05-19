#include <stdint.h>
#include <Device/IO.h>
#include "Parallel.h"
#include "Serial.h"
#include <Abstraction/Console.h>

uint16_t* ParallelAddress = (uint16_t*)0x408;
uint8_t ParallelRegister = 0;

void ParallelWrite(uint8_t Data)
{
	outb(*ParallelAddress + ParallelRegister, Data);
}

uint8_t ParallelRead()
{
	return inb(*ParallelAddress + ParallelRegister);
}

void SetParallelRegister(uint8_t Register)
{
	ParallelRegister = Register;
}
void ParallelWriteByte(uint8_t Data)
{
	unsigned char lControl;
	uint8_t Value = inb(*ParallelAddress + 1);
	while (!(Value & 0x80))
	{
		Value = inb(*ParallelAddress + 1);
	}

	outb(*ParallelAddress, Data);
	lControl = inb(*ParallelAddress + 2);
	outb(*ParallelAddress + 2, lControl | 1);
	outb(*ParallelAddress + 2, lControl);
	Value = inb(*ParallelAddress + 1);
	while (!(Value & 0x80))
	{
		Value = inb(*ParallelAddress + 1);
	}
}
void ParallelWriteString(char* Data) 
{
	while (*Data != '\0')
	{
		ParallelWriteByte(*Data);
		Data++;
	}
}