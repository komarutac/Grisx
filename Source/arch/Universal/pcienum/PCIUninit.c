#include <Abstraction/DAL.h>
#include <PCI.h>

void PCIUninit(DALDevice* Device)
{
	Device->SendKrnMessage(MsgDevUnloaded, Device);
	return;
}