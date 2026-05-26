#include <string.h>
#include <stdint.h>
#include <stddef.h>

int memcmp(const void* APointer, const void* BPointer, size_t Length)
{
    const uint8_t* A = (const uint8_t*)APointer;
    const uint8_t* B = (const uint8_t*)BPointer;

    for (size_t i = 0; i < Length; i++)
    {
        if (A[i] < B[i])
        {
            return -1;
        }
        else if (B[i] < A[i])
        {
            return 1;
        }
    }

    return 0;
}