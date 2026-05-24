#include <Abstraction/DAL.h>
#include <Device/CPU/PIC.h>
#include <Device/IO.h>

void PICUninit(DALDevice* Device) {
	DisablePIC();
	Device->SendKrnMessage(MsgDevUnloaded, PICDevice);
}