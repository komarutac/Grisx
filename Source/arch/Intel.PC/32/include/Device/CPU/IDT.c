#include "IDT.h"
#include <stdint.h>
#include <string.h>
#include "ISRS.h"
#include <Abstraction/Console.h>
#include <PPI.h>
IDTEntry IDT[256];
IDTPointer IDTP;

void IDTSetGate(uint8_t Index, uint64_t Base, uint16_t Selector, uint8_t Flags) {
    IDT[Index].BaseLow = Base & 0xFFFF;
    IDT[Index].BaseHigh = (Base >> 16) & 0xFFFF;
    IDT[Index].Always0 = 0;
    IDT[Index].Selector = Selector;
    IDT[Index].Flags = Flags;
}

void IDTInstall() {
    IDTP.Limit = (sizeof(IDTEntry) * 256) - 1;
    IDTP.Base = (uint32_t)&IDT;
    memset(&IDT, 0, sizeof(IDTEntry) * 256);
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
    lidt(IDTP);
}