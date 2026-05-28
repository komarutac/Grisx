#include <string.h>
#include <stdint.h>
#include <stddef.h>

void* memcpy(void* APointer, void* BPointer, size_t Length)
{
    uint8_t* A = (const uint8_t*)APointer;
    uint8_t* B = (const uint8_t*)BPointer;

    for (size_t i = 0; i < Length; i++)
    {
        A[i] = B[i];
    }

    return A;
}