#include <stdint.h>
#include <vgatext.h>
#include <Abstraction/Console.h>
#include <stddef.h>

void VCWriteChar(uint8_t Char) {
	switch (Char) {
		case '\n':
			VCNewLine();
			VCWriteChar('\r');
			return;
		case '\t':
			for (size_t i = 0; i < VCIndent; i++) {
				VCWriteChar(' ');
				VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
			}
			return;
		case '\b':
			DefaultConsole->X--;
			VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
			return;
		case '\r':
			DefaultConsole->X = 0;
			VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
			return;
	}

	VCAddEntry(DefaultConsole->TextBuffer, VCCharEntry(Char, VCTextColor));

	if (DefaultConsole->X++ + 1 == VCResWidth) {
		DefaultConsole->X = 0;
		if (DefaultConsole->Y++ + 1 == VCResHeight) {
			VCScrollDown();
			DefaultConsole->Y--;
		}
	}

	VMoveCursor(DefaultConsole->Y, DefaultConsole->X);
}