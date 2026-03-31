#pragma once
#include <stdint.h>
#define outb(port, val) __asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory")
#define outl(port, val) __asm volatile ("outl %k0, %w1" : : "a"(val), "Nd"(port) : "memory")
#define outw(port, val) __asm volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port) : "memory")
#define IOWait() outb(0x80, 0)

struct _CommandQueueEntry {
	uint16_t Port;
	uint8_t Value;
}; typedef struct _CommandQueueEntry CommandQueueEntry;

extern uint8_t inb(uint16_t port);
extern uint16_t inw(uint16_t port);
extern uint32_t inl(uint16_t port);