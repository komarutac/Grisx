#include <Abstraction/DAL.h>
#include <PCI.h>

void* PCICommand(char Function, void* Arguments, DALDevice* Device)
{
	(void)Device;
	switch (Function)
	{
		case DevCMDHasFunction:
			break;
	}
	return 0;
}