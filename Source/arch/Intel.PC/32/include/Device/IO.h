#pragma once
#include <stdint.h>
#define outb(port, val) __asm volatile ("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory")
#define outl(port, val) __asm volatile ("outl %k0, %w1" : : "a"(val), "Nd"(port) : "memory")
#define outw(port, val) __asm volatile ("outw %w0, %w1" : : "a"(val), "Nd"(port) : "memory")
#define inb(Port, A) __asm volatile ("inb %w1, %b0" : "=a"(A) : "Nd"(Port) : "memory")
#define inw(Port, A) __asm volatile ("inw %w1, %w0" : "=a"(A) : "Nd"(Port) : "memory")
#define inl(Port, A) __asm volatile ("inl %w1, %k0" : "=a"(A) : "Nd"(Port) : "memory")
#define IOWait() outb(0x80, 0)

struct _CommandQueueEntry {
	uint16_t Port;
	uint8_t Value;
}; typedef struct _CommandQueueEntry CommandQueueEntry;