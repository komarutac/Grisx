#include <stddef.h>
#include <vgatext.h>
#include <Abstraction/Console.h>
#include <stdbool.h>

void VCClear() {
	DefaultConsole->Status |= 0b0001; // Set busy bit
	for (size_t i = 0; i < VCResWidth * VCResHeight; i++) {
		VCTextBuffer0[i] = VCCharEntry(' ', VCTextColor);
	}
	DefaultConsole->Status &= ~0b0001; // Clear busy bit
}