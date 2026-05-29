#include <stdint.h>
#include <stddef.h>
#include <vgatext.h>
#include <Abstraction/Console.h>

void VCAddEntry(uint16_t* Array, uint16_t Entry) {
	const size_t Index = VCCreateIndex(DefaultConsole->Y, DefaultConsole->X);
	if (Array[Index] != Entry) {
		Array[Index] = Entry;
	}
}