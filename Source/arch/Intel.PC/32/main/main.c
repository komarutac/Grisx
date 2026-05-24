#include <Device/VGA/ColorTextMode.h>
#include <Abstraction/Console.h>
#include "main.h"
#include <KernelMain.h>
#include <Device/CPU/GDT.h>

void SetupTextMode()
{
	VCClear();
	VCLoadConsolePointers();
}

void SetupVideo()
{
	SetupTextMode();
	DebugConsole = NullConsole;
}

void Loader() {
	SetupVideo();
	KernelMain();
}