#pragma once
#include <stdint.h>
#define Color(A,R,G,B) (ARGB){.Alpha=A,.Red=R,.Green=G,.Blue=B}
struct _ARGB {
    uint8_t Alpha;
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
};
typedef struct _ARGB ARGB;