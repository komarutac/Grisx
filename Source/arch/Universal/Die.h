#pragma once
#include <Device/CPU/Interrupt.h>
#include <stdbool.h>
#include <stdint.h>
#include <macro.h>
#include <stdnoreturn.h>

extern dependent void DieFault(char* Message, Registers* Regs, bool Die);
extern independent void Oops(char* Reason, char* What);
extern independent void Alert(char* Reason, char* What);
extern independent noreturn void Stop(char* Message, uint32_t Code);