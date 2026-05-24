#include <Device/IO.h>
#include <Device/CPU/PIT.h>

void PlayPCBeep() {
    uint8_t Temp = inb(0x61);

    if (Temp != (Temp | 3)) {
        outb(0x61, Temp | 3);
    }
}