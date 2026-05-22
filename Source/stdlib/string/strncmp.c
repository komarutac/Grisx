#include "string.h"
#include <stdint.h>
#include <stddef.h>

int strncmp(char* A, char* B, size_t Length)
{
    if (strlen(A) > Length || strlen(B) > Length)
    {
        return -1;
    }

    for (size_t i = 0; i < strlen(A); i++)
    {
        if (i < Length)
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
    }

    return 0;
}