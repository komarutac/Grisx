#include <vgatext.h>
#include <stdint.h>
#include <Abstraction/Console.h>
#include <stddef.h>

void VCScrollDown() {
	for (uint8_t Top = VCResTop; Top < DefaultConsole->Y; Top++) {
		for (uint8_t Left = VCResLeft; Left < VCResWidth; Left++) {
			const uint16_t IndexAbove = VCCreateIndex(Top + 1, Left);
			const uint16_t Index = VCCreateIndex(Top, Left);
			DefaultConsole->TextBuffer[Index] = DefaultConsole->TextBuffer[IndexAbove];
		}
	}

	for (uint8_t Left = VCResLeft; Left < DefaultConsole->Width; Left++) {
		const size_t Index = VCCreateIndex(DefaultConsole->Y, Left);
		DefaultConsole->TextBuffer[Index] = VCCharEntry(' ', VCTextColor);
	}
}