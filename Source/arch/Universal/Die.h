#pragma once
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>

extern void DieFault(char* Message, Registers* Regs, bool Die);
extern void Oops(char* Reason, char* What);
extern void Alert(char* Reason, char* What);