#include <Abstraction/Console.h>
#include <main.h>

void SetupVideo()
{
	VCClear();
	VCLoadConsolePointers();
	DebugConsole = NullConsole;
}