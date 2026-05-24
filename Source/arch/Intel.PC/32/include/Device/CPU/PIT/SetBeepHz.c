#include <Device/IO.h>
#include <Device/CPU/PIT.h>

void SetBeepHz(int HZ) {
    int Divisor = 1193180 / HZ;
    outb(PITCommand, 0xB6);
    outb(PITChannel2, Divisor & 0xFF);
    outb(PITChannel2, Divisor >> 8);
}