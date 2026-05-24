#include <KernelMain.h>

void KernelMain()
{
	InitVFS();
	InitPlatformDevices();
	InitPCIEnum();
	FindDiskCtrl();
}