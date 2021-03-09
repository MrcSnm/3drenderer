#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>
#include "../def.h"

typedef struct color
{
    float r,g,b,a
};

color unpack_rgba(uint32_t color);
uint32_t pack_rgba(ubyte r, ubyte g, ubyte b, ubyte a);
uint32_t color_pack_rgba(color c);

#endif