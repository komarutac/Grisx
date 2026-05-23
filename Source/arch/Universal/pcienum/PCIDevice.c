#include <Abstraction/DAL.h>
#include <PCI.h>

DALDevice* PCIDevice = &(DALDevice)
{
	.Name = "pcienum",
	.Properties = &(DALProperties)
    {
		.Bus = DeviceBusCPU,
		.Type = DeviceTypeBus,
	},
	.Uninitialize = PCIUninit,
	.Initialize = PCIInit,
	.Command = PCICommand
};