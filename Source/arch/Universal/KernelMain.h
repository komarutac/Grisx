#pragma once
#include <Abstraction/DAL.h>

extern void KernelMain();
extern void InitPCIEnum();
extern void InitPlatformDevices();
extern void InitVFS();
extern DALDevice* FindDiskCtrl();