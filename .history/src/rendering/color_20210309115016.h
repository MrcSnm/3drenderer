#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>

typedef struct color
{
    float r,g,b,a
};

color unpack_rgba(uint32_t color);

#endif