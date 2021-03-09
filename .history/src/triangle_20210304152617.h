#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "vector.h"

typedef struct face_t
{
    int a,b,c, d;
} face_t;

typedef struct triangle_t
{
    vec2 points[3];
} triangle_t;


face_t[2] face_triangulate(face_t f);

#endif