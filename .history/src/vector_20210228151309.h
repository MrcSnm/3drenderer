#ifndef VECTOR_H
#define VECTOR_H

typedef union vec2
{
    float values[2];
    struct{float x, y;};
} vec2;

typedef union vec3
{
    float values[3];
    struct{float x, y, z;};
} vec3;

#endif
