#include <Device/IO.h>
#include <Device/CPU/PIT.h>

void StopPCBeep() {
    uint8_t Temp = inb(0x61);
    outb(0x61, Temp & 0xFC);
}