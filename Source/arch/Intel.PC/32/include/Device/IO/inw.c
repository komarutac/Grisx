#include <Device/IO.h>
#include <stdint.h>

uint16_t inw(int Port)
{
	uint16_t Value;
	__asm volatile ("inw %w1, %w0" : "=a"(Value) : "Nd"(Port) : "memory");
	return Value;
}