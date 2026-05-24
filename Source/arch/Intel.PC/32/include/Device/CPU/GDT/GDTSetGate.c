#include <stdint.h>
#include <Device/CPU/GDT.h>

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