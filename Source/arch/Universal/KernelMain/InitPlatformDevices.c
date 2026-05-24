#include <Abstraction/AAL.h>
#include <Abstraction/PAL.h>
#include <Abstraction/DAL.h>

void InitPlatformDevices()
{
	RegisterDALDevice(ArchDevice, MessageCallback);
	RegisterDALDevice(PALDevice, MessageCallback);
}
