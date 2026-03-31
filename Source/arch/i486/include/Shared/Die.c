#include "Die.h"
#include <Device/Terminal/Console.h>
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>
#include <Color.h>

void DieFault(char* Message, Registers* Regs, bool Die) {
	//VCLoadConsolePointers();
	//VCClear();
	//VCLoadCommandQueue();
	//VCExecuteCommandQueue();
	//VCSetFont(VCFont8x8, 8);
	//DefaultConsole.SetBackgroundColor((ARGB){255, CTMWhite, 0, 0});
	//DefaultConsole.SetForegroundColor((ARGB){255, CTMBlack, 0, 0});

	ConFormatTo(DefaultConsole, "Start Exception\n");
	ConFormatTo(DefaultConsole, "	Message : %s\n", Message);
	ConFormatTo(DefaultConsole, "	Fault : 0x%h\n", Regs->Fault);
	ConFormatTo(DefaultConsole, "	CS : 0x%h\n", Regs->CS);
	ConFormatTo(DefaultConsole, "	DS : 0x%h\n", Regs->DS);
	ConFormatTo(DefaultConsole, "	EAX : 0x%h\n", Regs->EAX);
	ConFormatTo(DefaultConsole, "	EBP : 0x%h\n", Regs->EBP);
	ConFormatTo(DefaultConsole, "	EBX : 0x%h\n", Regs->EBX);
	ConFormatTo(DefaultConsole, "	ECX : 0x%h\n", Regs->ECX);
	ConFormatTo(DefaultConsole, "	EDI : 0x%h\n", Regs->EDI);
	ConFormatTo(DefaultConsole, "	EDX : 0x%h\n", Regs->EDX);
	ConFormatTo(DefaultConsole, "	EFLAGS : 0x%h\n", Regs->EFLAGS);
	ConFormatTo(DefaultConsole, "	EIP : 0x%h\n", Regs->EIP);
	ConFormatTo(DefaultConsole, "	Vector : 0x%h\n", Regs->InterruptNumber);
	ConFormatTo(DefaultConsole, "	ES : 0x%h\n", Regs->ES);
	ConFormatTo(DefaultConsole, "	ESI : 0x%h\n", Regs->ESI);
	ConFormatTo(DefaultConsole, "	ESP : 0x%h\n", Regs->ESP);
	ConFormatTo(DefaultConsole, "	FS : 0x%h\n", Regs->FS);
	ConFormatTo(DefaultConsole, "	GS : 0x%h\n", Regs->GS);
	ConFormatTo(DefaultConsole, "	SS : 0x%h\n", Regs->SS);
	ConFormatTo(DefaultConsole, "	USERESP : 0x%h\n", Regs->UserESP);
	ConFormatTo(DefaultConsole, "End Exception\n");

	if (Die) {
		__asm ("cli");
		__asm ("hlt");
	}
}