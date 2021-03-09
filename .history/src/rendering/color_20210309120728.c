#include "color.h"


color_u unpack_rgba(uint32_t c)
{
    return (color_u){.r = c >> 24, .g = (c >> 16) & 256, .b = (c >> 8) & 256, .a = c & 256};
}
uint32_t pack_argb(ubyte a, ubyte r, ubyte g, ubyte b)
{
    return (a<<24)+(r<<16)+(g<<8)+b;
}
uint32_t pack_rgba(ubyte r, ubyte g, ubyte b, ubyte a)
{
    return (r<<24)+(g<<16)+(b<<8)+a;
}
uint32_t color_pack_argb(color_u c)
{
    return pack_argb(c.a, c.r, c.g, c.b);
}
uint32_t color_pack_rgba(color_u c)
{
    return pack_rgba(c.r, c.g, c.b, c.a);
}

color_f color_f_from_color_u(color_u c)
{
    float m = 255.0f;
    return (color_f){}
}

