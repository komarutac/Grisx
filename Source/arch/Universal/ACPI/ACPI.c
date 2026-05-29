#include <stdint.h>
#include <stddef.h>
#include <Abstraction/DAL.h>
#include "ACPI.h"
#include "RSDP.h"
#include <Abstraction/Console.h>
#include <string.h>
#include <balloc.h>
#include <macro.h>

ACPILookupEntry* ACPILookupTable;
size_t ACPILookupIndex;

// TODO: Make the SearchForRSDP function better
size_t SearchForRSDP()
{
	for (size_t i = 0x000E0000; i < 0x000FFFFF; i++)
	{
		uint8_t* Data = (uint8_t*)i;

		if (Data != NULL)
		{
			char* Lookup = "RSD PTR ";
			bool Bad;
				
			for (int j = 0; j < 8; j++)
			{
				if (Data[j] != Lookup[j])
				{
					Bad = true;
					break;
				}
				else
				{
					Bad = false;
				}
			}
			
			if (!Bad)
			{
				return i;
			}
		}
	}
	return NULL;
}

void ACPIUninit(DALDevice* Device)
{
	Device->SendKrnMessage(MsgDevUnloaded, Device);
}

void ACPIInit(DALDevice* Device)
{
	size_t RSDPPtr = SearchForRSDP();

	if (RSDPPtr != NULL)
	{
		RSDP* ACPIRSDP = (RSDP*)RSDPPtr;
		RSDT* ACPIRSDT = (RSDT*)ACPIRSDP->RSDTAddress;
		ACPILookupEntry* Current;
		size_t TotalBytes = 0;
		int TotalTables = 0;
		TotalTables++;
		TotalBytes += ACPIRSDT->Size;

		ACPILookupTable = allocator(bump, alloc)(sizeof(ACPILookupEntry*));
		Current = ACPILookupTable;
		
		for (uint64_t i = 0; i < (ACPIRSDT->Size - sizeof(SDT)) / 4; i++)
		{
			SDT* Table = (SDT*)ACPIRSDT->OtherSDT[i];
			Current->Pointer = Table;
			Current->Next = allocator(bump, alloc)(sizeof(ACPILookupEntry));
			Current = Current->Next;
	
			TotalTables++;
			TotalBytes += Table->Size;
		}
		
		Device->SendKrnMessage(MsgDevReady, Device);
	}
	else
	{
		Device->SendKrnMessage(MsgDevError, Device);
	}
}

void* ACPICommand(int Function, void* Arguments, DALDevice* Device)
{
	(void)Function;
	(void)Arguments;
	(void)Device;
	return NULL;
}

void ACPINoDriverInit(DALDevice* Device)
{
	Device->SendKrnMessage(MsgDevError, Device);
}


DALDevice* ACPISystem = &(DALDevice)
{
	.Name = "acpienum",
	.Properties = &(DALProperties) {
		.Bus = DeviceBusCPU,
		.Type = DeviceTypePowerManagement
	},
	.Uninitialize = ACPIUninit,
	.Initialize = ACPIInit,
	.Command = ACPICommand
};
