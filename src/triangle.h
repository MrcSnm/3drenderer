#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "math/vector.h"
#include "rendering/texture.h"

typedef struct face_t
{
    int a,b,c,d;
    tex2D a_uv, b_uv, c_uv, d_uv;

    uint32_t color;
} face_t;

typedef struct triangle_t
{
    vec2 points[3]; 
    tex2D texCoords[3];   
    uint32_t color;
    float avg_depth;
} triangle_t;

// TODO: Draw a textured triangle


#endif