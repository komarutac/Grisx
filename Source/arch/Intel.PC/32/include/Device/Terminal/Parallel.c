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
	uint8_t Value;
	inb(*ParallelAddress + ParallelRegister, Value);
	return Value;
}

void SetParallelRegister(uint8_t Register)
{
	ParallelRegister = Register;
}
void ParallelWriteByte(uint8_t Data)
{
	unsigned char lControl;
	uint8_t Value;
	inb(*ParallelAddress + 1, Value);
	while (!(Value & 0x80))
	{
		inb(*ParallelAddress + 1, Value);
	}

	outb(*ParallelAddress, Data);
	inb(*ParallelAddress + 2, lControl);
	outb(*ParallelAddress + 2, lControl | 1);
	outb(*ParallelAddress + 2, lControl);
	inb(*ParallelAddress + 1, Value);
	while (!(Value & 0x80))
	{
		inb(*ParallelAddress + 1, Value);
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