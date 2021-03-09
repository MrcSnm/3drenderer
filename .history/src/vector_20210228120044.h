#ifndef VECTOR_H
#define VECTOR_H

typedef struct vec2
{
    union
    {
        struct {float x, y;};
        float values[2];
    };
    
} vec2;

typedef struct vec3
{
    union
    {
        struct{float x, y, z;};
        struct{float r, g, b;};
        float values[3];
    };
    
} vec3;

#endif
