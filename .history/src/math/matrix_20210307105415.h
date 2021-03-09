#ifndef MATRIX_H
#define MATRIX_H

typedef struct mat4
{
    float m[4][4]
} mat4;


mat4 mat4_identity(void);
mat4 mat4_scale_mat(float sx, float sy, float sz);


#endif