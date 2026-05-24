#include <Abstraction/DAL.h>
#include <Device/CPU/PIT.h>
#include <Device/CPU/ISRS.h>

void PITInit(DALDevice* Device) {
	SetTimerHz(100);
	SetBeepHz(800);
	RegisterIRQHandler(0, TimerHandler);
	Device->SendKrnMessage(MsgDevReady, Device);
}