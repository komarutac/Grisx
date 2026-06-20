#include <Device/CPU/GDT.h>
#include <stdint.h>

void GDTInstall()
{
    GP.Limit = (sizeof(GDTEntry) * 3) - 1;
    GP.Base = (uint32_t)&GDT;
    GDTSetGate(0, 0, 0, 0, 0);
    GDTSetGate(1, 0, 0xFFFFFFFF, Access(0, 1, 1, 0, 1, 0), Granularity(1, 1, 0, 15));
    GDTSetGate(2, 0, 0xFFFFFFFF, Access(0, 1, 0, 0, 1, 0), Granularity(1, 1, 0, 15));
    GDTFlush();
}