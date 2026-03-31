#pragma once
#include <stdint.h>
struct _ARGB {
    uint8_t Alpha;
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
};
typedef struct _ARGB ARGB;

struct _RGB {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
};
typedef struct _RGB RGB;

struct _BGR {
    unsigned char Blue;
    unsigned char Green;
    unsigned char Red;
};
typedef struct _BGR BGR;