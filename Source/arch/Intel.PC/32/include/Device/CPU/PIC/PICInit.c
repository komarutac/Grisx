#include <Abstraction/DAL.h>
#include <Device/CPU/PIC.h>
#include <Device/IO.h>

void PICInit(DALDevice* Device) {
	RemapPIC(0x20, 0x28);
	Device->SendKrnMessage(MsgDevReady, PICDevice);
}