#include "color.h"


color unpack_rgba(uint32_t c)
{
    return (color){.r = c << 24, .g = (c << 16) & 255, b = (c << 8)}
}
uint32_t pack_argb(ubyte a, ubyte r, ubyte g, ubyte b)
{

}
uint32_t pack_rgba(ubyte r, ubyte g, ubyte b, ubyte a)
{

}
uint32_t color_pack_argb(color c)
{

}
uint32_t color_pack_rgba(color c)
{

}
