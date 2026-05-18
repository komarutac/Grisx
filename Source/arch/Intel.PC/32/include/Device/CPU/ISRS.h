#ifndef C_CPU_ISRS_HEADER
#define C_CPU_ISRS_HEADER
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>
// http://www.osdever.net/bkerndev/Docs/isrs.htm
extern bool ISRFaultDie;
extern char* ExceptionMessages[32];
extern void DivisionByZeroException();
extern void DebugException();
extern void NonMaskableInterruptException();
extern void BreakpointException();
extern void OverflowException();
extern void OutOfBoundsException();
extern void InvalidOpcodeException();
extern void DeviceNotAvailableException();
extern void DoubleFaultException();
extern void CoprocessorSegmentOverrunException();
extern void BadTSSException();
extern void SegmentNotPresentException();
extern void StackFaultException();
extern void GeneralProtectionFaultException();
extern void PageFaultException();
extern void UnknownInterruptException();
extern void CoprocessorFaultException();
extern void AlignmentCheckException();
extern void MachineCheckException();
extern void SIMDFloatingPointException();
extern void VirtualizationException();
extern void ControlProtectionFault();
extern void ProgrammableInterruptTimerInterrupt();
extern void KeyboardInterrupt();
extern void CascadeInterrupt();
extern void COM2Interrupt();
extern void COM1Interrupt();
extern void LPT2Interrupt();
extern void FloppyDiskInterrupt();
extern void LPT1Interrupt();
extern void CMOSRTCInterrupt();
extern void FreeInterrupt0();
extern void FreeInterrupt1();
extern void FreeInterrupt2();
extern void MouseInterrupt();
extern void UnitInterrupt();
extern void PrimaryATAInterrupt();
extern void SecondaryATAInterrupt();
extern void SystemCall();
extern void TestSyscall();

extern void* IRQRoutines[255];
void RegisterIRQHandler(int IRQ, void (*Handler)(Registers* Regs));
void UnregisterIRQHanlder(int IRQ);
void ISRSInstall();
Registers* ISRHandler(Registers* Regs);
#endif