#include "matrix.h"

mat4 mat4_identity(void)
{
    return (mat4){{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    }};
}

mat4 mat4_scale_mat(float sx, float sy, float sz)
{
    return (mat4){{
        {sx, 0, 0, 0},
        {0, sy, 0, 0},
        {0, 0, sz, 0},
        {0, 0, 0,  1}
    }};
}