#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>
#include "../def.h"

typedef struct color_u
{
    ubyte r,g,b,a;
} color_u;

typedef struct color_f
{
    float r,g,b,a;
} color_f;


color_u unpack_rgba(uint32_t c);
uint32_t pack_argb(ubyte ar, ubyte r, ubyte g, ubyte b);
uint32_t pack_rgba(ubyte r, ubyte g, ubyte b, ubyte a);
uint32_t color_pack_argb(color c);
uint32_t color_pack_rgba(color c);

#endif