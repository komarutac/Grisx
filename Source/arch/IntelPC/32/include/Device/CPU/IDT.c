#include "IDT.h"
#include <stdint.h>
#include <string.h>
#include "ISRS.h"
#include <Device/Terminal/Console.h>
IDTEntry IDT[256];
IDTPointer IDTP;

void IDTSetGate(uint8_t Index, uint64_t Base, uint16_t Selector, uint8_t Flags) {
    IDT[Index].BaseLow = Base & 0xFFFF;
    IDT[Index].BaseHigh = (Base >> 16) & 0xFFFF;
    IDT[Index].Always0 = 0;
    IDT[Index].Selector = Selector;
    IDT[Index].Flags = Flags;
}

void IDTInstall() {
    IDTP.Limit = (sizeof(IDTEntry) * 256) - 1;
    IDTP.Base = (uint32_t)&IDT;
    memset(&IDT, 0, sizeof(IDTEntry) * 256);
    ISRSInstall();
    IDTLoad();
}