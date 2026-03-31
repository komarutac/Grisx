#pragma once
#include <stdint.h>
#include <stdbool.h>
 
 
// Directories and files must be in a directory or in root.
// Root must be the first entry.
// Example:
// Root Block
//		File Block
//		Directory Block
//			File Block
//			File Block
//		End Directory Block
//		File Block
// End Root Block

struct _Block {
	char Type[4]; // BLOB
	unsigned long Length;
	unsigned char* Data;
} __attribute__((packed));

typedef struct _Block Block;