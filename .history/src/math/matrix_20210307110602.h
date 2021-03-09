#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"

typedef struct mat4
{
    float m[4][4]
} mat4;


mat4 mat4_identity(void);
mat4 mat4_scale_mat(float sx, float sy, float sz);

vec4 mat4_mult(mat4 m, vec4 v);


#endif