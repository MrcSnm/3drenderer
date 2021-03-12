#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdint.h>


typedef struct tex2D
{
    float u,v;
} tex2D;

extern const uint8_t REDBRICK_TEXTURE[];
extern uint32_t* mesh_texture;
extern int texture_width;
extern int texture_height;

#endif