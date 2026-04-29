#include "IO.h"
#include <stdint.h>

uint8_t inb(uint16_t port) {
	uint8_t ret = 0;
	__asm volatile ("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint16_t inw(uint16_t port) {
	uint16_t ret = 0;
	__asm volatile ("inw %w1, %w0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

uint32_t inl(uint16_t port) {
	uint32_t ret = 0;
	__asm volatile ("inl %w1, %k0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}