#include <Abstraction/Console.h>
#include <vgatext.h>

void VCLoadConsolePointers() {
	DefaultConsole->Status |= 0b0001; // Set busy bit
	DefaultConsole->X = 0;
	DefaultConsole->Y = 0;
	DefaultConsole->Width = VCResWidth;
	DefaultConsole->Height = VCResHeight;
	DefaultConsole->Clear = &VCClear;
	DefaultConsole->WriteChar = &VCWriteChar;
	DefaultConsole->WriteString = &VCWriteString;
	DefaultConsole->SetForegroundColor = &VCSetForegroundColor;
	DefaultConsole->SetBackgroundColor = &VCSetBackgroundColor;
	DefaultConsole->WriteCharAt = &VCWriteCharAt;
	DefaultConsole->TextBuffer = VCConsoleBuffer;
	DefaultConsole->Status &= ~0b0001; // Clear busy bit
}