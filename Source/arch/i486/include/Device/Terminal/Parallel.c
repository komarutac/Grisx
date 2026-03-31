#include <stdint.h>
#include <Device/IO.h>
#include "Parallel.h"
#include "Serial.h"
#include <Device/Terminal/Console.h>

uint16_t* ParallelAddress = (uint16_t*)0x408;
uint8_t ParallelRegister = 0;

void ParallelWrite(uint8_t Data) {
	outb(*ParallelAddress + ParallelRegister, Data);
}
uint8_t ParallelRead() {
	return inb(*ParallelAddress + ParallelRegister);
}

void SetParallelRegister(uint8_t Register) {
	ParallelRegister = Register;
}
void ParallelWriteByte(uint8_t Data) {
	unsigned char lControl;
	while (!(inb(*ParallelAddress + 1) & 0x80));
	outb(*ParallelAddress, Data);
	lControl = inb(*ParallelAddress + 2);
	outb(*ParallelAddress + 2, lControl | 1);
	outb(*ParallelAddress + 2, lControl);
	while (!(inb(*ParallelAddress + 1) & 0x80));
}
void ParallelWriteString(char* Data) {
	while (*Data != '\0') {
		ParallelWriteByte(*Data);
		Data++;
	}
}
void LoadParallelDebugPointers() {
	//ConFormatTo(DefaultConsole, "Initializing parallel...\r");
	if (*ParallelAddress == 0) {
		DebugConsole = DefaultConsole;
		return;
	}
	SetParallelRegister(2);
	ParallelWrite(ParallelRead() & 0xDF);
	SetParallelRegister(0);
	ParallelWrite(0xFF);
	
	DebugConsole->Busy = 1;
	DebugConsole->X = 0;
	DebugConsole->Y = 0;
	DebugConsole->WriteChar = &ParallelWriteByte;
	DebugConsole->WriteString = &ParallelWriteString;
	DebugConsole->WriteLine = &ParallelWriteString;
	DebugConsole->Busy = 0;
	//ConFormatTo(DefaultConsole, "Initializing parallel... Ok\n");
}