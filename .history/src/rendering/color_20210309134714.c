#include "color.h"


color_u color_u_unpack_rgba(uint32_t c)
{
    return (color_u){.r = c >> 24, .g = (c >> 16) & 255, .b = (c >> 8) & 255, .a = c & 255};
}
color_u color_u_unpack_argb(uint32_t c)
{
    return (color_u){.a = c >> 24, .r = (c >> 16) & 255, .g = (c >> 8) & 255, .b = c & 255};
}
uint32_t pack_argb(ubyte a, ubyte r, ubyte g, ubyte b)
{
    return (a<<24)+(r<<16)+(g<<8)+b;
}
uint32_t pack_rgba(ubyte r, ubyte g, ubyte b, ubyte a)
{
    return (r<<24)+(g<<16)+(b<<8)+a;
}
uint32_t color_u_pack_argb(color_u c)
{
    return pack_argb(c.a, c.r, c.g, c.b);
}
uint32_t color_u_pack_rgba(color_u c)
{
    return pack_rgba(c.r, c.g, c.b, c.a);
}

uint32_t color_u_multiply(uint32_t c, float rate)
{
    
}

color_f color_f_from_color_u(color_u c)
{
    float m = 255.0f;
    return (color_f){.r = c.r/m, .g = c.g/m, .b = c.b/m, .a = c.a/m};
}