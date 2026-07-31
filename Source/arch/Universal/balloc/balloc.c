#include <stddef.h>
#include <balloc.h>
#include <Abstraction/Console.h>
#include <string.h>
#include <macro.h>

char Blocks[2048 * 2];
int Offset = 0;

void* allocator(bump, alloc)(int Size)
{
	if (sizeof(Blocks) - Offset < Size)
	{
		ConFormatTo(DefaultConsole, "Total Blocks %d, Free Blocks %d, Allocate %d Blocks Failed\r\n", sizeof(Blocks), sizeof(Blocks) - Offset, Size);
		return NULL;
	}

	void* Pointer = &Blocks + Offset;
	Offset += Size;
	return Pointer;
}

void bclear()
{
	memset(Blocks, 0, sizeof(Blocks));
	Offset = 0;
}