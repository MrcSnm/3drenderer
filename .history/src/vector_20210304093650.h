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


/////////////////////////////////////////////////////////////////////
// Vector 2D Functions
/////////////////////////////////////////////////////////////////////

float vec2_mag(vec2 v);
float vec2_dot(vec2 a, vec2 b);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, float factor);
vec2 vec2_div(vec2 a, float factor);

/////////////////////////////////////////////////////////////////////
// Vector 3D Functions
/////////////////////////////////////////////////////////////////////
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 a, float factor);
vec3 vec3_div(vec3 a, float factor);
float vec3_mag(vec3 v);
float vec3_dot(vec3 a, vec3 b);
vec3 vec3_cross(vec3 a, vec3 b);
vec3 vec3_rotateZ(vec3 v, float angle);
vec3 vec3_rotateY(vec3 v, float angle);
vec3 vec3_rotateX(vec3 v, float angle);
void vec3_debug(vec3 v);


#endif
