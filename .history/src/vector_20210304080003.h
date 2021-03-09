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
inline vec2 vec2_add(vec2 a, vec2 b);
inline vec2 vec2_sub(vec2 a, vec2 b);
inline vec2 vec2_scale(vec2 a, float scale);

/////////////////////////////////////////////////////////////////////
// Vector 3D Functions
/////////////////////////////////////////////////////////////////////
inline vec3 vec3_add(vec3 a, vec3 b);
inline vec3 vec3_sub(vec3 a, vec3 b);
inline vec3 vec3_scale(vec3 a, float scale);
inline float vec3_mag(vec3 v);

inline vec3 vec3_rotateZ(vec3 v, float angle);
inline vec3 vec3_rotateY(vec3 v, float angle);
inline vec3 vec3_rotateX(vec3 v, float angle);
inline vec3 vec3_scale(vec3 v, float amount);
void vec3_debug(vec3 v);


#endif
