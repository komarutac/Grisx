#include <Abstraction/Console.h>
#include <main.h>
#include <vgatext.h>

void SetupVideo()
{
	VCClear();
	VCLoadConsolePointers();
	DebugConsole = NullConsole;
}