#pragma once
#include <Device/CPU/Interrupt.h>
#include <DAL.h>
#include <stdint.h>

extern char KeyboardBuffer[1024];
extern uint8_t KeyboardBufferIndex;
extern volatile void* KeyboardEvent[5];
extern char CurrentLayout[];
extern void ClearKeyboardBuffer();
extern void KeyboardHandler(Registers* Regs);
extern void KeyboardUninit(DALDevice* Device);
extern void KeyboardInit(DALDevice* Device);
extern DALDevice* KeyboardDevice;
