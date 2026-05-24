#include <Device/CPU/PIC.h>
#include <Abstraction/DAL.h>

DALDevice* PICDevice = &(DALDevice){
	.Name = "interruptctrl",
	.Properties = &(DALProperties) {
		.Bus = DeviceBusISA,
		.Type = DeviceTypePIC,
	},
	.Uninitialize = PICUninit,
	.Initialize = PICInit
};