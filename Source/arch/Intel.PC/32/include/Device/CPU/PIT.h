#ifndef C_DEVICE_CPU_PIT_HEADER
#define C_DEVICE_CPU_PIT_HEADER
#include <Device/IO.h>
#include <Abstraction/Console.h>
#include <Device/CPU/Interrupt.h>
#include <Abstraction/DAL.h>
#define PITCommand 0x43
#define PITChannel1 0x40
#define PITChannel2 0x41
#define PITChannel3 0x42

extern volatile int TimerTicks;
extern volatile int TimerSeconds;
extern volatile Registers LastRegisters;
extern DALDevice* PITDevice;

void SetTimerHz(int HZ);
void SetBeepHz(int HZ);
void PlayPCBeep();
void StopPCBeep();
void TimerCheck();
void TimerHandler(Registers* Regs);
void TimerWait(int Ticks);
extern void PITInit();
extern void PITUninit();
void* PITCommandFunc(int Function, void* Arguments, DALDevice* Device);
void PITInit(DALDevice* Device);
void PITUninit(DALDevice* Device);
#endif