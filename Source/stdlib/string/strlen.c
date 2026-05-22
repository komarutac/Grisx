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
