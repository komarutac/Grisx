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
		DefaultConsole->SetForegroundColor((ARGB) {.Red = 0xF});
		DefaultConsole->SetBackgroundColor((ARGB) {.Red = 0xC});
		printf("Fatal error.\r\n");
	}
	else if (Regs->InterruptNumber == 3)
	{
		DefaultConsole->SetForegroundColor((ARGB) {.Red = 0xF});
		DefaultConsole->SetBackgroundColor((ARGB) {.Red = 0xE});
		printf("Paused.\r\n");
		SerialWriteString("{ACK=0}");
		SerialWriteString("{READY=0}");
		SerialWriteString("{PAUSE=1}");
		SerialWriteString("{EIP=&H");
		size_t BaseLength = GetSizeForBase(Regs->EIP, 16) + 1;
		char NumberString[BaseLength];
		IntegerToASCII(Regs->EIP, NumberString, SBase16, 16);
		SerialWriteString(NumberString);
		SerialWriteString("}");
	}
	
	DefaultConsole->SetForegroundColor((ARGB) {.Red = 0x7});
	DefaultConsole->SetBackgroundColor((ARGB) {.Red = 0x0});
	printf("Fault 0x%X, CS 0x%X, DS 0x%X, EAX 0x%X, EBP 0x%X, EBX 0x%X, ECX 0x%X, EDI 0x%X, EDX 0x%X, EFLAGS 0x%X, EIP 0x%X, INT 0x%X, ES 0x%X, ESI 0x%X, ESP 0x%X, FS 0x%X, GS 0x%X, SS 0x%X, USERESP 0x%X\r\n", Regs->Fault, Regs->CS, Regs->DS, Regs->EAX, Regs->EBP, Regs->EBX, Regs->ECX,
	Regs->EDI, Regs->EDX, Regs->EFLAGS, Regs->EIP, Regs->InterruptNumber, Regs->ES, Regs->ESI, Regs->ESP, Regs->FS, Regs->GS, Regs->SS, Regs->UserESP);
	if (Regs->EIP > (unsigned int)&StartProgram && Regs->EIP < (unsigned int)&EndProgram)
	{
		printf("Program Range: Kernel <0x%X-0x%X>\r\n", &StartProgram, &EndProgram);
	}
	else
	{
		printf("Program Range: Unknown\r\n");
	}

	uint32_t CR0 = GetCR0();
	uint32_t CR3 = GetCR3();

	printf("Control Register 0: ");
	printf("PG %d, ", CR0 & CR0PG);
	printf("CD %d, ", CR0 & CR0CD);
	printf("NW %d, ", CR0 & CR0NW);
	printf("AM %d, ", CR0 & CR0AM);
	printf("WP %d, ", CR0 & CR0WP);
	printf("NE %d, ", CR0 & CR0NE);
	printf("ET %d, ", CR0 & CR0ET);
	printf("TS %d, ", CR0 & CR0TS);
	printf("EM %d, ", CR0 & CR0EM);
	printf("MP %d, ", CR0 & CR0MP);
	printf("PE %d\r\n", CR0 & CR0PE);

	printf("Control Register 2: 0x%X\r\n", GetCR2());
	printf("Control Register 3: ");
	printf("PBDR %d, ", CR3 & CR3PBDR);
	printf("PCD %d, ", CR3 & CR3PCD);
	printf("PWT %d\r\n", CR3 & CR3PWT);
			
	printf("EFLAGS: ");
	printf("TF %d, ", Regs->EFLAGS & EFLAGSTF);
	printf("IF %d, ", Regs->EFLAGS & EFLAGSIF);
	printf("IPOL %d, ", Regs->EFLAGS & EFLAGSIPOL);
	printf("NF %d, ", Regs->EFLAGS & EFLAGSNF);
	printf("RF %d, ", Regs->EFLAGS & EFLAGSRF);
	printf("VM %d, ", Regs->EFLAGS & EFLAGSVM);
	printf("AC %d\r\n", Regs->EFLAGS & EFLAGSAC);

	printf("Message: %s\r\n", Message);

	if (Regs->InterruptNumber == 3)
	{
		SerialWriteString("{READY=1}");
	}
	else
	{
		__asm ("cli");
	}
	
	
	for (;;)
	{
		if (Regs->InterruptNumber == 3)
		{
			if (SerialRead() == '{')
			{
				if (SerialRead() == 'P' &&
					SerialRead() == 'A' &&
					SerialRead() == 'U' &&
					SerialRead() == 'S' &&
					SerialRead() == 'E' &&
					SerialRead() == '=' &&
					SerialRead() == '0' &&
					SerialRead() == '}')
				{
					SerialWriteString("{PAUSE=0}");
					SerialWriteString("{READY=0}");
					SerialWriteString("{ACK=1}");
				}
				return Regs;
			}
		}
		else
		{
			__asm ("hlt");
		}
	}
}