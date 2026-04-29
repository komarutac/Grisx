#include <Die.h>
#include <Device/Terminal/Console.h>
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>

void DieFault(char* Message, Registers* Regs, bool Die)
{
	(void)Die;
	printf("Exception: %s\r\n", Message);
	printf("Fault 0x%h, CS 0x%h, DS 0x%h, EAX 0x%h, EBP 0x%h, EBX 0x%h, ECX 0x%h, EDI 0x%h, EDX 0x%h, EFLAGS 0x%h, EIP 0x%h, INT 0x%h, ES 0x%h, ESI 0x%h, ESP 0x%h, FS 0x%h, GS 0x%h, SS 0x%h, USERESP 0x%h\r\n", Regs->Fault, Regs->CS, Regs->DS, Regs->EAX, Regs->EBP, Regs->EBX, Regs->ECX,
	Regs->EDI, Regs->EDX, Regs->EFLAGS, Regs->EIP, Regs->InterruptNumber, Regs->ES, Regs->ESI, Regs->ESP, Regs->FS, Regs->GS, Regs->SS, Regs->UserESP);
	printf("End Exception\r\n");
	for (;;);
}
