#pragma once
#include <stdint.h>
#include <stddef.h>
struct _Stream {
    int Position;
    void* Context;
    int (*Read)(struct _Stream Stream, char* Array, size_t Position, size_t Length);
    int (*Write)(struct _Stream Stream, char* Array, size_t Position, size_t Length);
    int (*Seek)(struct _Stream Stream);
}; typedef struct _Stream Stream;