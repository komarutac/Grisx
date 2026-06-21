#include <Device/CPU/Interrupt.h>
#include <stdint.h>
#include <Abstraction/Console.h>

Registers* SyscallHandler(Registers* Regs)
{
    if (Regs->ECX == 1)
    {
        Regs->EAX = 1;
        return Regs;
    }

    Regs->EAX = 0;
    return Regs;
}