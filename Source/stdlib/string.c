#include "string.h"
#include <stdint.h>
#include <stddef.h>

size_t strlen(char* String)
{
    size_t Length = 0;
    while (*String != '\0')
    {
        Length++;
        String++;
    }
    return Length;
}

int strcmp(char* A, char* B)
{
    // TODO: Replace before push
    return 0;
}

void* memset(void* Pointer, size_t Value, size_t Size) {
    uint8_t* Buffer = (uint8_t*)Pointer;
    for (size_t i = 0; i < Size; i++) {
        Buffer[i] = (uint8_t)Value;
    }
    return Pointer;
}

int memcmp(const void* APointer, const void* BPointer, size_t Length) {
    const uint8_t* a = (const uint8_t*)APointer;
    const uint8_t* b = (const uint8_t*)BPointer;
    for (size_t i = 0; i < Length; i++) {
        if (a[i] < b[i])
            return -1;
        else if (b[i] < a[i])
            return 1;
    }
    return 0;
}