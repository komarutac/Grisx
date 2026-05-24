#include <Device/IO.h>
#include <stdint.h>

unsigned long inl(int Port)
{
	unsigned long Value;
	__asm volatile ("inl %w1, %k0" : "=a"(Value) : "Nd"(Port) : "memory");
	return Value;
}