#include "string.h"
#include <stdint.h>
#include <stddef.h>

void* memset(void* Pointer, size_t Value, size_t Size)
{
    uint8_t* Buffer = (uint8_t*)Pointer;

    for (size_t i = 0; i < Size; i++)
    {
        Buffer[i] = (uint8_t)Value;
    }

    return Pointer;
}