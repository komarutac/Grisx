#include <Device/CPU/GDT.h>
#include <stdint.h>

void GDTInstall()
{
    GP.Limit = (sizeof(GDTEntry) * 3) - 1;
    GP.Base = (uint32_t)&GDT;
    GDTSetGate(0, 0, 0, 0, 0);
    GDTSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    GDTSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    GDTFlush();
}