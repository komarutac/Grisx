#include <Device/CPU/Paging.h>
#include <Device/CPU/CR.h>

void DisablePaging()
{
    uint32_t CR0 = GetCR0();
    CR0 &= ~CR0PG;
    SetCR0(CR0);
}