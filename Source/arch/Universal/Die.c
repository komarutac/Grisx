#include <Die.h>
#include <Abstraction/Console.h>
#include <Make.h>
#include <PPI.h>
#include <stdint.h>

void Oops(char* Reason, char* What)
{
	(void)What;
	printf(" Oops, %s.\r\n", Reason);
}

void Alert(char* Reason, char* What)
{
	(void)What;
	printf("Alert, %s!\r\n", Reason);
}

void Stop(char* Message, uint32_t Code) {
	printf("MK Macros: %s %s %s-Bits\r\n", MkName, MkVersion, MkBits);
	printf("Trace (Preprocessor): %s\r\n", PPICurrentFunction);
	printf("Stop: %s 0x%X\r\n", Message, Code);
}