#include <Device/CPU/ISRS.h>
#include <Device/CPU/IDT.h>
#include <Device/CPU/PIC.h>
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>
#include <Die.h>
#include <Abstraction/Console.h>
#include <PPI.h>

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
    IRQRoutines[IRQ + 32] = Handler;
}

void UnregisterIRQHanlder(int IRQ)  {
    IRQRoutines[IRQ + 32] = 0;
}

void ISRSInstall() {
    PPITrace(__FUNCTION__);
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
    IDTInstall();
}

Registers* ISRHandler(Registers* Regs) {
    if (Regs->InterruptNumber < 32) {
        printf("CPU exception triggered\r\n");
        DieFault(ExceptionMessages[Regs->InterruptNumber], Regs, ISRFaultDie);
    }
    PPITrace(__FUNCTION__);

    if (Regs->InterruptNumber >= 32 && Regs->InterruptNumber <= 47) {
			//ConFormatTo(DefaultConsole, "IRQ %d triggered\n", Regs->InterruptNumber - 32);
		if (IRQRoutines[Regs->InterruptNumber] == 0) {
			if (Regs->InterruptNumber >= 40) {
				outb(PICSlave, PICEOI);
			}

			outb(PICMaster, PICEOI);
			return Regs;
		}
        void (*Handler)(Registers* Regs) = IRQRoutines[Regs->InterruptNumber];
        if (Handler) {
            PPICurrentFunction = "<unknown>";
            Handler(Regs);
        }

        if (Regs->InterruptNumber >= 40) {
            outb(PICSlave, PICEOI);
        }

        outb(PICMaster, PICEOI);
    }

    return Regs;
}