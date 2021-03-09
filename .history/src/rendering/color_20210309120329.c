#include "color.h"


color unpack_rgba(uint32_t c)
{
    return (color){.r = c >> 24, .g = (c >> 16) & 256, .b = (c >> 8) & 256, .a = c & 256};
}
uint32_t pack_argb(ubyte a, ubyte r, ubyte g, ubyte b)
{
    return (a<<24)+(r<<16)+(g<<8)+b;
}
uint32_t pack_rgba(ubyte r, ubyte g, ubyte b, ubyte a)
{
    return (r<<24)+(g<<16)+(b<<8)+a;
}
uint32_t color_pack_argb(color c)
{
    return pack_argb(c.a, c.r, c.g, c.b);
}
uint32_t color_pack_rgba(color c)
{

}
