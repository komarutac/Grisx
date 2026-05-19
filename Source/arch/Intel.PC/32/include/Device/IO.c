#include "IO.h"
#include <stdint.h>

uint8_t inb(int Port)
{
	uint8_t Value;
	__asm volatile ("inb %w1, %b0" : "=a"(Value) : "Nd"(Port) : "memory");
	return Value;
}

uint16_t inw(int Port)
{
	uint16_t Value;
	__asm volatile ("inw %w1, %w0" : "=a"(Value) : "Nd"(Port) : "memory");
	return Value;
}

unsigned long inl(int Port)
{
	unsigned long Value;
	__asm volatile ("inl %w1, %k0" : "=a"(Value) : "Nd"(Port) : "memory");
	return Value;
}