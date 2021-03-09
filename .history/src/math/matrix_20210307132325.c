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

mat4 mat4_transation_mat(float tx, float ty, float tz)
{
    return (mat4){{
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0,  1}
    }};
}

vec4 mat4_mult_vec4(mat4 m, vec4 v)
{
    vec4 ret;

    ret.x = v.x*m.m[0][0] + v.y*m.m[0][1] + v.z*m.m[0][2] + v.w*m.m[0][3];
    ret.y = v.x*m.m[1][0] + v.y*m.m[1][1] + v.z*m.m[1][2] + v.w*m.m[1][3];
    ret.z = v.x*m.m[2][0] + v.y*m.m[2][1] + v.z*m.m[2][2] + v.w*m.m[2][3];
    ret.w = v.x*m.m[3][0] + v.y*m.m[3][1] + v.z*m.m[3][2] + v.w*m.m[3][3];
    return ret;
}