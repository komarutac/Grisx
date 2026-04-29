#pragma once
#include <stdint.h>

extern void VDisableCursor();
extern uint16_t VGetCursorPosition();
extern void VEnableCursor(const uint8_t Start, const uint8_t End);
extern void VMoveCursor(const uint8_t Top, const uint8_t Left);