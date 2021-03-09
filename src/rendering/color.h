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


color_u  color_u_unpack_rgba(uint32_t c);
color_u  color_u_unpack_argb(uint32_t c);
uint32_t pack_argb(ubyte ar, ubyte r, ubyte g, ubyte b);
uint32_t pack_rgba(ubyte r, ubyte g, ubyte b, ubyte a);
uint32_t color_u_pack_argb(color_u c);
uint32_t color_u_pack_rgba(color_u c);
uint32_t color_argb_multiply(uint32_t c, float rate, bool multiplyAlpha);

color_f color_f_from_color_u(color_u c);

#endif