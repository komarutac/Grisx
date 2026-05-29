#include <Abstraction/Console.h>
#include <vgatext.h>

void VCLoadConsolePointers() {
	DefaultConsole->Busy = 1;
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
	DefaultConsole->Busy = 0;
	DefaultConsole->TextBuffer = VCConsoleBuffer;
}