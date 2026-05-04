#include "PIT.h"
#include <stdint.h>
#include <Device/IO.h>
#include <Device/Terminal/Console.h>
#include <stdbool.h>
#include "ISRS.h"

volatile int TimerTicks;
volatile int TimerSeconds;
volatile Registers LastRegisters;

DALDevice* PITDevice = &(DALDevice){
	.Name = "timer",
	.Properties = &(DALProperties) {
		.Bus = DeviceBusISA,
		.Type = DeviceTypeTimer,
	},
	.Uninitialize = PITUninit,
	.Initialize = PITInit,
	.Command = PITCommandFunc
};

void SetTimerHz(int HZ) {
    int Divisor = 1193180 / HZ;
    outb(PITCommand, 0x36);
    outb(PITChannel1, Divisor & 0xFF);
    outb(PITChannel1, Divisor >> 8);
}

void SetBeepHz(int HZ) {
    int Divisor = 1193180 / HZ;
    outb(PITCommand, 0xB6);
    outb(PITChannel2, Divisor & 0xFF);
    outb(PITChannel2, Divisor >> 8);
}

void PlayPCBeep() {
    uint8_t Temp = inb(0x61);

    if (Temp != (Temp | 3)) {
        outb(0x61, Temp | 3);
    }
}

void StopPCBeep() {
    uint8_t Temp = inb(0x61) & 0xFC;
    outb(0x61, Temp);
}

void TimerHandler(Registers* Regs) {
	(void)Regs;
}

void* PITCommandFunc(int Function, void* Arguments, DALDevice* Device) {
	(void)Device;
	if (Function == DevCMDAudioSetHz) {
		SetBeepHz(*(int*)Arguments);
	} else if (Function == DevCMDAudioPlayStop) {
		bool Play = *(bool*)Arguments;
		if (Play)
			PlayPCBeep();
		else
			StopPCBeep();
	}
	return 0;
}

void PITInit(DALDevice* Device) {
	SetTimerHz(100);
	SetBeepHz(800);
	RegisterIRQHandler(0, TimerHandler);
	Device->SendKrnMessage(MsgDevReady, Device);
}

void PITUninit(DALDevice* Device) {
	StopPCBeep();
	RegisterIRQHandler(0, 0);
	Device->SendKrnMessage(MsgDevUnloaded, Device);
}
