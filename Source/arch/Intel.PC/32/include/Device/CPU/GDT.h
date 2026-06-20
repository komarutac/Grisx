#pragma once
#include <stdint.h>
#define Access(DPL, S, E, DC, RW, A) 1 << 7 | DPL << 5 | S << 4 | E << 3 | DC << 2 | RW << 1 | A << 0
#define Granularity(G, D, A, Len) G << 7 | D << 6 | A << 4 | Len

// http://www.osdever.net/bkerndev/Docs/gdt.htm

struct _GDTEntry
{
    uint16_t LimitLow;
    uint16_t BaseLow;
    uint8_t BaseMiddle;
    uint8_t Access;
    uint8_t Granularity;
    uint8_t BaseHigh;
} __attribute__((packed)); typedef struct _GDTEntry GDTEntry;

struct _GDTPointer
{
    uint16_t Limit;
    uint32_t Base;
} __attribute__((packed)); typedef struct _GDTPointer GDTPointer;

extern void GDTFlush();
extern void GDTSetGate(uint8_t Index, uint64_t Base, uint64_t Limit, uint8_t Access, uint8_t Granularity);
extern void GDTInstall();
extern GDTEntry GDT[3];
extern GDTPointer GP;