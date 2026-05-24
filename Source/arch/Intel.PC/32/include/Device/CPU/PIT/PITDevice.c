#include <Device/CPU/PIT.h>
#include <Abstraction/DAL.h>

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