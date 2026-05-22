#include "string.h"
#include <stdint.h>
#include <stddef.h>

int strcmp(char* A, char* B)
{
    if (strlen(A) != strlen(B))
    {
        return -1;
    }

    for (size_t i = 0; i < strlen(A); i++)
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