#include <Abstraction/Console.h>
#include "main.h"

void SetupVideo()
{
	SetupTextMode();
	DebugConsole = NullConsole;
}