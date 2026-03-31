#include <stdint.h>
#include <stddef.h>
#include <DAL.h>
#include "ACPI.h"
#include "RSDP.h"
#include <Device/Terminal/Console.h>
#include <Device/Memory.h>
#include <Device/CPU/PIT.h>

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

void PrintSDT(SDT* Table)
{
	char Magic[sizeof(Table->Magic) + 1];
	for (int i = 0; i < sizeof(Table->Magic); i++)
	{
		Magic[i] = Table->Magic[i];
	}
	Magic[sizeof(Table->Magic)] = '\0';
	ConFormatTo(DefaultConsole, "Found ACPI Table: %s %d bytes.\n", Magic, Table->Size);
}

void ACPIInit(DALDevice* Device)
{
	size_t RSDPPtr = SearchForRSDP();

	if (RSDPPtr != NULL)
	{
		RSDP* ACPIRSDP = (RSDP*)RSDPPtr;
		RSDT* ACPIRSDT = (RSDT*)ACPIRSDP->RSDTAddress;
		size_t TotalBytes = 0;
		int TotalTables = 0;
		TotalTables++;
		TotalBytes += ACPIRSDT->Size;
		
		for (uint64_t i = 0; i < (ACPIRSDT->Size - sizeof(SDT)) / 4; i++)
		{
			SDT* Table = (SDT*)ACPIRSDT->OtherSDT[i];
			PrintSDT(Table);
			if (memcmp(Table->Magic, "SSDT", 4) == 0 || memcmp(Table->Magic, "DSDT", 4) == 0 ||
				memcmp(Table->Magic, "PSDT", 4) == 0)
			{
				ConFormatTo(DefaultConsole, "Found %d bytes of AML code.\n", Table->Size - sizeof(SDT));
			}
			else if (memcmp(Table->Magic, "FACP", 4) == 0)
			{
				FADT* FixedTable = (FADT*)Table;
				if (FixedTable->SMICmdPort == 0 || FixedTable->ACPIEnable == 0)
				{
					ConFormatTo(DefaultConsole, "ACPI cannot be enabled.\n");
					Device->SendKrnMessage(MsgDevError, Device);
				}
				ConFormatTo(DefaultConsole, "Power management profile: %d %s\n", 
				FixedTable->PowerMgmtProfile, 
				FixedTable->PowerMgmtProfile == 0 ? "Unknown" : 
				FixedTable->PowerMgmtProfile == 1 ? "Desktop" :
				FixedTable->PowerMgmtProfile == 2 ? "Mobile" :
				FixedTable->PowerMgmtProfile == 3 ? "Workstation" :
				FixedTable->PowerMgmtProfile == 4 ? "Enterprise Server" : "Unknown");
			}
			TotalTables++;
			TotalBytes += Table->Size;
		}
		
		ConFormatTo(DefaultConsole, "Found %d ACPI tables %d bytes total.\n", TotalTables, TotalBytes);
		Device->SendKrnMessage(MsgDevReady, Device);
	}
	else
	{
		Device->SendKrnMessage(MsgDevError, Device);
	}
}

void* ACPICommand(int Function, void* Arguments, DALDevice* Device)
{
	return NULL;
}

void ACPINoDriverInit(DALDevice* Device)
{
	Device->SendKrnMessage(MsgDevError, Device);
}


DALDevice* ACPISystem = &(DALDevice)
{
	.Name = "ACPI System",
	.Bus = DeviceBusCPU,
	.Type = DeviceTypePowerManagement,
	.Uninitialize = ACPIUninit,
	.Initialize = ACPIInit,
	.Command = ACPICommand
};
