#ifndef VECTOR_H
#define VECTOR_H
#include "../def.h"
///Expands to angle degrees 
#define DEGREES(angle) (M_PI/180*(angle))

#ifdef SIMD
#include <xmmintrin.h>
#endif

typedef struct vec2
{
    #ifdef SIMD
    union{
        __m64 data;
        struct {float x, y;};
    };
    #else
    float x, y;
    #endif
} vec2;

typedef struct vec3
{
    float x, y, z;
} vec3;

typedef struct vec4
{
    #ifdef SIMD
    union
    {
        __m128 data;
        struct{float x, y, z, w;};
        
        /* data */
    };
    
    #else
        float x, y, z, w;
    #endif
} vec4;


/////////////////////////////////////////////////////////////////////
// Vector 2 Functions
/////////////////////////////////////////////////////////////////////

float vec2_mag(vec2 v);
void vec2_normallize(vec2* a);
float vec2_dot(vec2 a, vec2 b);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, float factor);
vec2 vec2_div(vec2 a, float factor);

/////////////////////////////////////////////////////////////////////
// Vector 3 Functions
/////////////////////////////////////////////////////////////////////
vec3 vec3_add(vec3 a, vec3 b);
vec3 vec3_sub(vec3 a, vec3 b);
vec3 vec3_mul(vec3 a, float factor);
vec3 vec3_div(vec3 a, float factor);
float vec3_mag(vec3 v);
float vec3_dot(vec3 a, vec3 b);
void vec3_normallize(vec3* a);
vec3 vec3_cross(vec3 a, vec3 b);
vec3 vec3_rotateZ(vec3 v, float angle);
vec3 vec3_rotateY(vec3 v, float angle);
vec3 vec3_rotateX(vec3 v, float angle);
void vec3_debug(vec3 v);

/////////////////////////////////////////////////////////////////////
// Vector conversion Functions
/////////////////////////////////////////////////////////////////////
vec4 vec4_from_vec3(vec3 input);
vec3 vec3_from_vec4(vec4 v);
// vec3 vec3_sub(vec3 a, vec3 b);
// vec3 vec3_mul(vec3 a, float factor);
// vec3 vec3_div(vec3 a, float factor);
// float vec3_mag(vec3 v);
// float vec3_dot(vec3 a, vec3 b);
// void vec3_normallize(vec3* a);
// vec3 vec3_cross(vec3 a, vec3 b);
// vec3 vec3_rotateZ(vec3 v, float angle);
// vec3 vec3_rotateY(vec3 v, float angle);
// vec3 vec3_rotateX(vec3 v, float angle);
// void vec3_debug(vec3 v);

#endif
