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
extern DALDevice* PITDevice;

extern void SetTimerHz(int HZ);
extern void SetBeepHz(int HZ);
extern void PlayPCBeep();
extern void StopPCBeep();
extern void TimerCheck();
extern void TimerHandler(Registers* Regs);
extern void TimerWait(int Ticks);
extern void PITInit();
extern void PITUninit();
extern void* PITCommandFunc(int Function, void* Arguments, DALDevice* Device);
extern void PITInit(DALDevice* Device);
extern void PITUninit(DALDevice* Device);
#endif