#include <Device/IO.h>
#include <Device/CPU/PIT.h>

void SetTimerHz(int HZ) {
    int Divisor = 1193180 / HZ;
    outb(PITCommand, 0x36);
    outb(PITChannel1, Divisor & 0xFF);
    outb(PITChannel1, Divisor >> 8);
}