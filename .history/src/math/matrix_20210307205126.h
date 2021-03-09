#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef float mat4;


mat4 mat4_identity(void);
mat4 mat4_scale_mat(float sx, float sy, float sz);
mat4 mat4_translation_mat(float tx, float ty, float tz);
mat4 mat4_rotationX_mat(float angle);
mat4 mat4_rotationY_mat(float angle);
mat4 mat4_rotationZ_mat(float angle);
mat4 mat4_mult_mat4(mat4 a, mat4 b);
vec4 mat4_mult_vec4(mat4 m, vec4 v);


#endif