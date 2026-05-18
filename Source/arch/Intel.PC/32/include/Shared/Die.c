#include <Die.h>
#include <Abstraction/Console.h>
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>
#include <Abstraction/AAL.h>
#include <stddef.h>
#include <PPI.h>
#include <Build/Make.h>
#include <Build/Linker.h>

void DieFault(char* Message, Registers* Regs, bool Die)
{
	(void)Die;
	printf("Fault 0x%X, CS 0x%X, DS 0x%X, EAX 0x%X, EBP 0x%X, EBX 0x%X, ECX 0x%X, EDI 0x%X, EDX 0x%X, EFLAGS 0x%X, EIP 0x%X, INT 0x%X, ES 0x%X, ESI 0x%X, ESP 0x%X, FS 0x%X, GS 0x%X, SS 0x%X, USERESP 0x%X\r\n", Regs->Fault, Regs->CS, Regs->DS, Regs->EAX, Regs->EBP, Regs->EBX, Regs->ECX,
	Regs->EDI, Regs->EDX, Regs->EFLAGS, Regs->EIP, Regs->InterruptNumber, Regs->ES, Regs->ESI, Regs->ESP, Regs->FS, Regs->GS, Regs->SS, Regs->UserESP);
	if (Regs->EIP > &StartProgram && Regs->EIP < &EndProgram)
	{
		printf("Program Range: Kernel <0x%X-0x%X>\r\n", &StartProgram, &EndProgram);
	}
	else
	{
		printf("Program Range: Unknown\r\n");
	}
	printf("Register Struct: 0x%X\r\n", Regs);
	Stop(Message, 0x2000400);
	ArchDevice->Command(AALDisableInterrupts, NULL, ArchDevice);
	ArchDevice->Command(AALHalt, NULL, ArchDevice);
}