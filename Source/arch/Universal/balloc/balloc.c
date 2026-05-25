#include <stddef.h>
#include <balloc.h>
#include <Abstraction/Console.h>
#include <string.h>

char Blocks[2048 * 2];
int Offset = 0;

void* balloc(int Size)
{
	if (sizeof(Blocks) - Offset < Size)
	{
		ConFormatTo(DefaultConsole, "Total Blocks %d, Free Blocks %d, Allocate %d Blocks Failed\r\n", sizeof(Blocks), sizeof(Blocks) - Offset, Size);
		return NULL;
	}

	ConFormatTo(DefaultConsole, "Allocated %d blocks\r\n", Size);

	void* Pointer = &Blocks + Offset;
	Offset += Size;
	return Pointer;
}

void bclear()
{
	ConFormatTo(DefaultConsole, "Bump allocator clear\r\n");
	memset(Blocks, 0, sizeof(Blocks));
}