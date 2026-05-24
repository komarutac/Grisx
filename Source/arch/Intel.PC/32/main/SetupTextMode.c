#include "main.h"
#include <Device/VGA/ColorTextMode.h>

void SetupTextMode()
{
	VCClear();
	VCLoadConsolePointers();
}