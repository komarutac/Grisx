#include "ISRS.h"
#include "IDT.h"
#include "PIC.h"
#include "Interrupt.h"
#include <stdbool.h>
#include <Shared/Die.h>
#include <Device/Terminal/Console.h>

bool ISRFaultDie = true;
void* IRQRoutines[255];
char* ExceptionMessages[32] = {
    "Divide Error",
    "Debug Exception",
    "NMI Interrupt",
    "Breakpoint",
    "INTO-detected Overflow",
    "BOUND Range Exceeded",
    "Illegal Opcode",
    "Device Not Available",
    "Double Fault",
    "Co-processor Segment Overrun",
    "Invalid Task State Segment",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Fault"
};

void RegisterIRQHandler(int IRQ, void (*Handler)(Registers* Regs)) {
	ConFormatTo(DefaultConsole, "Registering IRQ %d handler 0x%h...\n", IRQ, Handler);
    IRQRoutines[IRQ + 32] = Handler;
}

void UnregisterIRQHanlder(int IRQ)  {
	ConFormatTo(DefaultConsole, "Unregistering IRQ %d handler...\n", IRQ);
    IRQRoutines[IRQ + 32] = 0;
}

void ISRSInstall() {
	ConFormatTo(DefaultConsole, "Setting exception interrupts...\n");
    IDTSetGate(0, (unsigned)DivisionByZeroException, 0x08, 0x8E);
    IDTSetGate(1, (unsigned)DebugException, 0x08, 0x8E);
    IDTSetGate(2, (unsigned)NonMaskableInterruptException, 0x08, 0x8E);
    IDTSetGate(3, (unsigned)BreakpointException, 0x08, 0x8E);
    IDTSetGate(4, (unsigned)OverflowException, 0x08, 0x8E);
    IDTSetGate(5, (unsigned)OutOfBoundsException, 0x08, 0x8E);
    IDTSetGate(6, (unsigned)InvalidOpcodeException, 0x08, 0x8E);
    IDTSetGate(7, (unsigned)DeviceNotAvailableException, 0x08, 0x8E);
    IDTSetGate(8, (unsigned)DoubleFaultException, 0x08, 0x8E);
    IDTSetGate(9, (unsigned)CoprocessorSegmentOverrunException, 0x08, 0x8E);
    IDTSetGate(10, (unsigned)BadTSSException, 0x08, 0x8E);
    IDTSetGate(11, (unsigned)SegmentNotPresentException, 0x08, 0x8E);
    IDTSetGate(12, (unsigned)StackFaultException, 0x08, 0x8E);
    IDTSetGate(13, (unsigned)GeneralProtectionFaultException, 0x08, 0x8E);
    IDTSetGate(14, (unsigned)PageFaultException, 0x08, 0x8E);
    IDTSetGate(15, (unsigned)UnknownInterruptException, 0x08, 0x8E);
    IDTSetGate(16, (unsigned)CoprocessorFaultException, 0x08, 0x8E);
    IDTSetGate(19, (unsigned)SIMDFloatingPointException, 0x08, 0x8E);
    IDTSetGate(20, (unsigned)VirtualizationException, 0x08, 0x8E);
    IDTSetGate(21, (unsigned)ControlProtectionFault, 0x08, 0x8E);

	ConFormatTo(DefaultConsole, "Setting ISA interrupts...\n");
    IDTSetGate(32, (unsigned)ProgrammableInterruptTimerInterrupt, 0x08, 0x8E);
    IDTSetGate(33, (unsigned)KeyboardInterrupt, 0x08, 0x8E);
    IDTSetGate(34, (unsigned)CascadeInterrupt, 0x08, 0x8E);
    IDTSetGate(35, (unsigned)COM2Interrupt, 0x08, 0x8E);
    IDTSetGate(36, (unsigned)COM1Interrupt, 0x08, 0x8E);
    IDTSetGate(37, (unsigned)LPT2Interrupt, 0x08, 0x8E);
    IDTSetGate(38, (unsigned)FloppyDiskInterrupt, 0x08, 0x8E);
    IDTSetGate(39, (unsigned)LPT1Interrupt, 0x08, 0x8E);
    IDTSetGate(40, (unsigned)CMOSRTCInterrupt, 0x08, 0x8E);
    IDTSetGate(41, (unsigned)FreeInterrupt0, 0x08, 0x8E);
    IDTSetGate(42, (unsigned)FreeInterrupt1, 0x08, 0x8E);
    IDTSetGate(43, (unsigned)FreeInterrupt2, 0x08, 0x8E);
    IDTSetGate(44, (unsigned)MouseInterrupt, 0x08, 0x8E);
    IDTSetGate(45, (unsigned)UnitInterrupt, 0x08, 0x8E);
    IDTSetGate(46, (unsigned)PrimaryATAInterrupt, 0x08, 0x8E);
    IDTSetGate(47, (unsigned)SecondaryATAInterrupt, 0x08, 0x8E);
    IDTSetGate(128, (unsigned)SystemCall, 0x08, 0x8E);
}

Registers* ISRHandler(Registers* Regs) {
    if (Regs->InterruptNumber < 32) {
        if (ISRFaultDie) {
            DieFault(ExceptionMessages[Regs->InterruptNumber], Regs, ISRFaultDie);
        }
    }

    if (Regs->InterruptNumber >= 32 && Regs->InterruptNumber <= 47) {
			//ConFormatTo(DefaultConsole, "IRQ %d triggered\n", Regs->InterruptNumber - 32);
		if (IRQRoutines[Regs->InterruptNumber] == 0) {
			ConFormatTo(DefaultConsole, "Error: no handler for IRQ %d\n", Regs->InterruptNumber - 32);
			if (Regs->InterruptNumber >= 40) {
				outb(PICSlave, PICEOI);
			}

			outb(PICMaster, PICEOI);
			return Regs;
		}
        void (*Handler)(Registers* Regs) = IRQRoutines[Regs->InterruptNumber];
        if (Handler) {
            Handler(Regs);
        }

        if (Regs->InterruptNumber >= 40) {
            outb(PICSlave, PICEOI);
        }

        outb(PICMaster, PICEOI);
    }

    return Regs;
}