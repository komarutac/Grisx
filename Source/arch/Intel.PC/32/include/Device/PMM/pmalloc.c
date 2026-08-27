#include <stdint.h>
#include <stddef.h>
#include <Device/PMM/Map.h>
#include <PMM.h>
#include <Abstraction/Console.h>
#include <Build/Linker.h>

void* pmalloc()
{
	for (uint32_t i = (uint32_t)MemoryMapTable; i < (uint32_t)MemoryMapTable + MemoryMapTableLength; i += 4)
	{
		uint32_t Byte = *(uint32_t*)i;

		if (Byte == 0x14)
		{
			MemoryMapEntry* MemMap = (MemoryMapEntry*)i;
			
			if (MemMap == 0)
			{
				continue;
			}

			if (MemMap->Address == 0 && MemMap->Length == 0)
			{
				continue;
			}

			if (MemMap->Type == MemoryMapTypeFree)
			{
				uint32_t Size = 0;
				for (int j = 0; j < 31; j++)
				{
					unsigned char Bit = MemMap->PMMFree >> j;
					if (Bit & ~0xFE)
					{
						MemMap->PMMFree &= ~(1 << j);
						FreeMemory -= Size;
						UsedMemory += Size;
						return (void*)(MemMap->Address + Size);
					}
					Size += 4096;
				}
			}
			
			i += sizeof(MemoryMapEntry) - 4;
		}
	}
	return 0;
}