#include "matrix.h"
#include <math.h>

mat4 mat4_identity(void)
{
    return (mat4){{
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}
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

mat4 mat4_translation_mat(float tx, float ty, float tz)
{
    return (mat4){{
        {1, 0, 0, tx},
        {0, 1, 0, ty},
        {0, 0, 1, tz},
        {0, 0, 0,  1}
    }};
}

mat4 mat4_rotationX_mat(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return (mat4){{
        {1,  0, 0, 0},
        {0,  c, s, 0},
        {0, -s, c, 0},
        {0,  0, 0, 1}
    }};
}

mat4 mat4_rotationY_mat(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return (mat4){{
        {c, 0, -s, 0},
        {0,  1, 0, 0},
        {s,  0, c, 0},
        {0,  0, 0, 1}
    }};
}

mat4 mat4_rotationZ_mat(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return (mat4){{
        {c, -s, 0, 0},
        {s,  c, 0, 0},
        {0,  0, 1, 0},
        {0,  0, 0, 1}
    }};
}

mat4 mat4_mult_mat4(mat4 a, mat4 b)
{
    mat4 m;
    for(int i = 0; i < 4; i++)
    {
        //C X R
        m.m[i][0] = a.m[i][0] * b.m[0][0]  + a.m[i][1] * b.m[1][0] + a.m[i][2]*b.m[2][0] + a.m[i][3]*b.m[3][0];
        m.m[i][1] = a.m[i][0] * b.m[0][1]  + a.m[i][1] * b.m[1][1] + a.m[i][2]*b.m[2][1] + a.m[i][3]*b.m[3][1];
        m.m[i][2] = a.m[i][0] * b.m[0][2]  + a.m[i][1] * b.m[1][2] + a.m[i][2]*b.m[2][2] + a.m[i][3]*b.m[3][2];
        m.m[i][3] = a.m[i][0] * b.m[0][3]  + a.m[i][1] * b.m[1][3] + a.m[i][2]*b.m[2][3] + a.m[i][3]*b.m[3][3];
    }
    return m;
}

mat4 mat4_perspective_mat(float aspect, float fov, float znear, float zfar)
{
    float fov_scale_factor = 1/tan(fov/2);
    float z_normallize = zfar/(zfar-znear);

    return (mat4){{
        {aspect*fov_scale_factor, 0, 0, 0},
        {0,        fov_scale_factor, 0, 0},
        {0,            0, z_normallize, -z_normallize*znear},
        {0, 0, 1,0} //Save original Z onto W
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

vec4 mat4_project(mat4 projectionMatrix, vec4 input)
{
    vec4 ret = mat4_mult_vec4(projectionMatrix, input);

    if(ret.w != 0.0)
    {
        ret.x/=ret.w;
        ret.y/=ret.w;
        ret.z/=ret.w;
    }
    return ret;
}
