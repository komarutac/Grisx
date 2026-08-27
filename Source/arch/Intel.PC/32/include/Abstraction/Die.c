#include <Die.h>
#include <Abstraction/Console.h>
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>
#include <Abstraction/AAL.h>
#include <stddef.h>
#include <PPI.h>
#include <Build/Make.h>
#include <Build/Linker.h>
#include <Device/CPU/CR.h>
#include <Device/CPU/EFLAGS.h>
#include <Device/Terminal/Serial.h>
#include <StringConvert.h>

Registers* DieFault(char* Message, Registers* Regs, bool Die)
{
	(void)Die;
	if (Regs->InterruptNumber != 3)
	{
		DefaultConsole->SetForegroundColor((ARGB) {.Red = 255, .Green = 255, .Blue = 255});
		DefaultConsole->SetBackgroundColor((ARGB) {.Red = 170});
		printf("Fatal error.\r\n");
	}
	else if (Regs->InterruptNumber == 3)
	{
		DefaultConsole->SetForegroundColor((ARGB) {.Red = 255, .Green = 255, .Blue = 255});
		DefaultConsole->SetBackgroundColor((ARGB) {.Red = 170, .Green = 85});
		printf("Paused.\r\n");
		SerialWriteByte(0xA1 /* WAIT */);
		SerialWriteByte(0xA2 /* BREAKPOINT */);
	}
	
	DefaultConsole->SetForegroundColor((ARGB) {.Red = 170, .Green = 170, .Blue = 170});
	DefaultConsole->SetBackgroundColor((ARGB) {});

	printf("Fault 0x%X, EBP 0x%X, EDI 0x%X, EIP 0x%X, INT 0x%X, ESI 0x%X, ESP 0x%X, USERESP 0x%X\r\n", Regs->Fault, Regs->EBP, Regs->EDI, Regs->EIP, Regs->InterruptNumber, Regs->ESI, Regs->ESP,
	Regs->UserESP);
	printf("AX: 0x%X, BX: 0x%X, CX: 0x%X, DX: 0x%X\r\n", Regs->AX, Regs->BX, Regs->CX, Regs->DX);
	printf("EAX: 0x%X, EBX: 0x%X, ECX: 0x%X, EDX: 0x%X\r\n", Regs->EAX, Regs->EBX, Regs->ECX, Regs->EDX);
	printf("CS: 0x%X, DS: 0x%X, ES: 0x%X, FS: 0x%X, GS: 0x%X, SS: 0z%X\r\n", Regs->CS, Regs->DS, Regs->ES, Regs->FS, Regs->GS, Regs->SS);

	uint32_t CR0 = GetCR0();
	uint32_t CR3 = GetCR3();

	printf("CR0: 0x%X, ", CR0);
	printf("CR2: 0x%X, ", GetCR2());
	printf("CR3: 0x%X, ", CR3);
	printf("EFLAGS: 0x%X\r\n", Regs->EFLAGS);
	printf("Message: %s\r\n", Message);

	if (Regs->EIP > (unsigned int)&StartProgram && Regs->EIP < (unsigned int)&EndProgram)
	{
		printf("Module: Kernel\r\n");
	}
	else
	{
		printf("Module: Unknown\r\n");
	}

	if (Regs->InterruptNumber == 3)
	{
		SerialWriteByte(0xA3 /* READY */);
	}
	else
	{
		__asm ("cli");
	}
	
	
	for (;;)
	{
		if (Regs->InterruptNumber == 3)
		{
			if (SerialRead() == 'c')
			{
				SerialWriteByte(0xA0 /* ACK */);
				return Regs;
			}
		}
		else
		{
			__asm ("hlt");
		}
	}
}