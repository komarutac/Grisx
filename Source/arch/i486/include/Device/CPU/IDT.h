#pragma once
#include <stdint.h>
// http://www.osdever.net/bkerndev/Docs/idt.htm

struct _IDTEntry {
    uint16_t BaseLow;
    uint16_t Selector;
    uint8_t Always0;
    uint8_t Flags;
    uint16_t BaseHigh;
} __attribute__((packed)); typedef struct _IDTEntry IDTEntry;

struct _IDTPointer {
    uint16_t Limit;
    uint32_t Base;
} __attribute__((packed)); typedef struct _IDTPointer IDTPointer;

extern void IDTLoad();
extern void IDTSetGate(uint8_t Index, uint64_t Base, uint16_t Selector, uint8_t Flags);
extern void IDTInstall();
extern IDTEntry IDT[256];