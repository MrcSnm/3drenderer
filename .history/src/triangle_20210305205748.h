#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vector.h"

typedef struct face_t
{
    int a,b,c,d;

    uint32_t color;
} face_t;

typedef struct triangle_t
{
    vec2 points[3];
    
    uint32_t color;
} triangle_t;


#endif