#include <PCI.h>
#include <KernelMain.h>
#include <Abstraction/DAL.h>

void InitPCIEnum()
{
	RegisterDALDevice(PCIDevice, MessageCallback);
}