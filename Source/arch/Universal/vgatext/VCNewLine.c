#include <vgatext.h>
#include <Abstraction/Console.h>
#include <stdbool.h>

void VCNewLine() {
	DefaultConsole->Status |= 0b0001; // Set busy bit

	if (DefaultConsole->Y++ == VCResHeight) {
		VCScrollDown();
		DefaultConsole->Y--;
	};

	VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
	DefaultConsole->Status &= ~0b0001; // Clear busy bit
}