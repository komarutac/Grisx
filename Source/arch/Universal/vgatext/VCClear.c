#include <stddef.h>
#include <vgatext.h>
#include <Abstraction/Console.h>
#include <stdbool.h>

void VCClear() {
	DefaultConsole->Busy = true;
	for (size_t i = 0; i < VCResWidth * VCResHeight; i++) {
		VCTextBuffer0[i] = VCCharEntry(' ', VCTextColor);
	}
	DefaultConsole->Busy = false;
}