#include <PMM.h>
#include <stdint.h>
#include <stdbool.h>
#include "Map.h"
#include <Abstraction/Console.h>
#include <Build/Linker.h>

bool PMMInit(void* MemoryMap, uint32_t Length)
{
	MemoryMapTable = (MemoryMapEntry*)MemoryMap;
	MemoryMapTableLength = Length;

	for (uint32_t i = (uint32_t)MemoryMap; i < (uint32_t)MemoryMap + Length; i += 4)
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
				if (MemMap->Address + MemMap->Length > &EndProgram ||
					MemMap->Address + MemMap->Length < &StartProgram)
				{
					if (MemMap->Address == 0)
					{
						MemMap->Address = 0x500;
					}
					
					uint32_t Size = 0;
					int Bad = 1;
					for (int j = 0; j < 31; j++)
					{
						if (MemMap->Address + Size > MemMap->Address + MemMap->Length)
						{
							printf("!");
							continue;
						}

						if (MemMap->Address + Size > &StartProgram &&
							MemMap->Address + Size < &EndProgram)
						{
							continue;
						}

						if (MemMap->Address + Size > 0xA0000 &&
							MemMap->Address + Size < 0xBFFFF)
						{
							continue;
						}

						if (MemMap->Address + Size < 1000000)
						{
							if (!(MemMap->Address + Size <= 0x7FFFF && MemMap->Address + Size >= 0x500))
							{
								continue;
							}
						}

						Bad = 0;
						MemMap->PMMFree |= (1 << j);
						Size += 4096;
					}

					if (Bad)
					{
						printf("@");
						MemMap->Type = MemoryMapTypeUsed;
					}

					FreeMemory += MemMap->Length;
					printf(".");
				}
				else
				{
					printf("#");
					MemMap->Type = MemoryMapTypeUsed;
				}
			}
			else if (MemMap->Type == MemoryMapTypeUsed)
			{
				printf("#");
				UsedMemory += MemMap->Length;
			}
			else
			{
				printf("?");	
			}
			
			
			i += sizeof(MemoryMapEntry) - 4;
		}
	}

	printf("]\r\n");

	if ((FreeMemory / 1024) < 4000)
	{
		printf("Warning: Free memory below recommended 4M\r\n");
	}
	
	printf("Free: %d, Used: %d\r\n", FreeMemory, UsedMemory);

	return true;
}