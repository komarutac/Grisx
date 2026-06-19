#include <Device/CPU/GDT.h>
#include <stdint.h>

void GDTInstall()
{
    GP.Limit = (sizeof(GDTEntry) * 3) - 1;
    GP.Base = (uint32_t)&GDT;
    GDTSetGate(0, 0, 0, 0, 0);
    GDTSetGate(1, 0, 0xFFFFFFFF, 1 << 7 | 0 << 5 | 1 << 4 | 10, 1 << 7 | 1 << 6 | 15);
    GDTSetGate(2, 0, 0xFFFFFFFF, 1 << 7 | 0 << 5 | 1 << 4 | 2, 1 << 7 | 1 << 6 | 15);
    GDTFlush();
}