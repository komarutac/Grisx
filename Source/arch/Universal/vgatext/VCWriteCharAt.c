#include <stddef.h>
#include <Abstraction/Console.h>
#include <vgatext.h>

void VCWriteCharAt(uint8_t Char, int X, int Y) {
	DefaultConsole->TextBuffer[VCCreateIndex(Y, X)] = VCCharEntry(Char, VCTextColor);
}