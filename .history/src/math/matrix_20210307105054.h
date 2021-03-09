#ifndef MATRIX_H
#define MATRIX_H

typedef struct mat4
{
    float m[4][4]
} mat4;


mat4 mat4_identity(void);


#endif