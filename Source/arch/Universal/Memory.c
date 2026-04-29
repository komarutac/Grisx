#include "Memory.h"
#include <stdint.h>
#include <stdbool.h>

MemoryBlock RealBlocks[1024];
MemoryBlock* Blocks[1024];

void* pmalloc(size_t Size) {
}

void pfree(void* Pointer) {
	// TODO: Make free function.
}