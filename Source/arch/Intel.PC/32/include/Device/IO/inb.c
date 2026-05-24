#include <Device/IO.h>
#include <stdint.h>

uint8_t inb(int Port)
{
	uint8_t Value;
	__asm volatile ("inb %w1, %b0" : "=a"(Value) : "Nd"(Port) : "memory");
	return Value;
}