#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"


#ifdef SIMD
#include <xmmintrin.h>
#endif

typedef struct mat4
{
    #ifdef SIMD
    union{
        __m128 m_4x[4];
        float m[4][4];
    };
    #else
    float m[4][4];
    #endif
} mat4;


mat4 mat4_identity(void);
mat4 mat4_scale_mat(float sx, float sy, float sz);
mat4 mat4_translation_mat(float tx, float ty, float tz);
mat4 mat4_rotationX_mat(float angle);
mat4 mat4_rotationY_mat(float angle);
mat4 mat4_rotationZ_mat(float angle);
mat4 mat4_mult_mat4(mat4 a, mat4 b);
vec4 mat4_mult_vec4(mat4 m, vec4 v);
mat4 mat4_perspective_mat(float aspect, float fov, float znear, float zfar);
mat4 mat4_look_at(vec3 eye, vec3 target, vec3 up);
vec4 mat4_project(mat4 projectionMatrix, vec4 input);


#endif