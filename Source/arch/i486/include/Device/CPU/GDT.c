#include "GDT.h"
#include <stdint.h>

GDTEntry GDT[3];
GDTPointer GP;

void GDTSetGate(uint8_t Index, uint64_t Base, uint64_t Limit, uint8_t Access, uint8_t Granularity)
{
    GDT[Index].BaseLow = (Base & 0xFFFF);
    GDT[Index].BaseMiddle = (Base >> 16) & 0xFF;
    GDT[Index].BaseHigh = (Base >> 24) & 0xFF;
    GDT[Index].LimitLow = (Limit & 0xFFFF);
    GDT[Index].Granularity = ((Limit >> 16) & 0x0F);
    GDT[Index].Granularity |= (Granularity & 0xF0);
    GDT[Index].Access = Access;
}

void GDTInstall()
{
    GP.Limit = (sizeof(GDTEntry) * 3) - 1;
    GP.Base = (uint32_t)&GDT;
    GDTSetGate(0, 0, 0, 0, 0);
    GDTSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    GDTSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    GDTFlush();
}