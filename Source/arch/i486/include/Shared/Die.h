#ifndef C_SHARED_DIE_HEADER
#define C_SHARED_DIE_HEADER
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>

void DieFault(char* Message, Registers* Regs, bool Die);
#endif