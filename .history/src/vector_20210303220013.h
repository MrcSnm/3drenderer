#ifndef VECTOR_H
#define VECTOR_H
#include "def.h"

typedef struct vec2
{
    float x, y;
} vec2;

typedef struct vec3
{
    float x, y, z;
} vec3;


vec3 vec3_rotateZ(vec3 v, float angle);
vec3 vec3_rotateY(vec3 v, float angle);
vec3 vec3_rotateX(vec3 v, float angle);
float vec3_mag(vec3 v);
void vec3_debug(vec3 v);

always_inline vec3 vec3_scale(vec3 v, float amount)
{
    return (vec3){
        .x = v.x*amount,
        .y = v.y*amount,
        .z = v.z*amount
    };
}


#endif
