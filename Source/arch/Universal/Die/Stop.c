#include <Die.h>
#include <Abstraction/Console.h>
#include <stdint.h>
#include <Build/Make.h>
#include <PPI.h>

void Stop(char* Message, uint32_t Code) {
	printf("MK Macros: %s %s %s-Bits\r\n", MkName, MkVersion, MkBits);
	printf("Trace (Preprocessor): %s\r\n", PPICurrentFunction);
	printf("Stop: %s 0x%X\r\n", Message, Code);
}