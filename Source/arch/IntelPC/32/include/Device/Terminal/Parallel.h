#pragma once
#include <stdint.h>

extern void ParallelWrite(uint8_t Data);
extern uint8_t ParallelRead();
extern void ParallelWriteByte(uint8_t Data);
extern void ParallelWriteString(char* Data);
extern void LoadParallelDebugPointers();