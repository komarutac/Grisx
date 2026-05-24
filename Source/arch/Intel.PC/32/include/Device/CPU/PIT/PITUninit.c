#include <Abstraction/DAL.h>
#include <Device/CPU/PIT.h>
#include <Device/CPU/ISRS.h>

void PITUninit(DALDevice* Device) {
	StopPCBeep();
	RegisterIRQHandler(0, 0);
	Device->SendKrnMessage(MsgDevUnloaded, Device);
}