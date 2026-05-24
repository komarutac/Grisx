#include <stdint.h>
#include <Device/CPU/IDT.h>

void IDTSetGate(uint8_t Index, uint64_t Base, uint16_t Selector, uint8_t Flags) {
    IDT[Index].BaseLow = Base & 0xFFFF;
    IDT[Index].BaseHigh = (Base >> 16) & 0xFFFF;
    IDT[Index].Always0 = 0;
    IDT[Index].Selector = Selector;
    IDT[Index].Flags = Flags;
}