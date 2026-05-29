#pragma once
#include <stdint.h>

struct _LoaderInfo
{
	uint32_t Flags;
	uint32_t UpperMemory;
	uint32_t LowerMemory;
	uint32_t BootDevice;
	uint32_t Arguments;
	uint32_t ModuleCount;
	uint32_t ModuleAddress;
}; typedef struct _LoaderInfo LoaderInfo;