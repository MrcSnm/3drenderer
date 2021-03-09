#ifndef VECTOR_H
#define VECTOR_H

typedef union vec2
{
    struct {float x, y;};
    float values[2];
} vec2;

typedef union vec3
{
    struct{float x, y, z};
    struct{float r, g, b;};
    float values[3];
} vec3;

#endif
