#include <vgatext.h>
#include <Abstraction/Console.h>
#include <stdbool.h>

void VCNewLine() {
	DefaultConsole->Busy = true;

	if (DefaultConsole->Y++ == VCResHeight) {
		VCScrollDown();
		DefaultConsole->Y--;
	};

	VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
	DefaultConsole->Busy = false;
}