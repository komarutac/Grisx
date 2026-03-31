#pragma once
struct _Registers
{
	unsigned int GS, FS, ES, DS;
	unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	unsigned int InterruptNumber, Fault;
	unsigned int EIP, CS, EFLAGS, UserESP, SS;
}; typedef struct _Registers Registers;