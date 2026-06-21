#pragma once
struct _Registers
{
	unsigned int GS, FS, ES, DS;
	unsigned short BX, DX, CX, AX;
	unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	unsigned int InterruptNumber, Fault;
	unsigned int EIP, CS, EFLAGS, UserESP, SS;
} __attribute__((packed)); typedef struct _Registers Registers;