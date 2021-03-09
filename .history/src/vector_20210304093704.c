#include "vector.h"
#include <stdio.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////
// Vector 2D Functions
/////////////////////////////////////////////////////////////////////
vec2 vec2_add(vec2 a, vec2 b)
{
    return (vec2){a.x+b.x, a.y+b.y};
}
vec2 vec2_sub(vec2 a, vec2 b)
{
    return (vec2){a.x-b.x, a.y-b.y};
}
vec2 vec2_mul(vec2 a, float factor)
{
    return (vec2){a.x*factor, a.y*factor};
}
vec2 vec2_div(vec2 a, float factor)
{
    return (vec2){a.x/factor, a.y/factor};
}

float vec2_mag(vec2 v)
{
    return sqrt(v.x*v.x+v.y*v.y);
}



/////////////////////////////////////////////////////////////////////
// Vector 3D Functions
/////////////////////////////////////////////////////////////////////
vec3 vec3_add(vec3 a, vec3 b)
{
    return (vec3){a.x +b.x, a.y+b.y, a.z+b.z};
}
vec3 vec3_sub(vec3 a, vec3 b)
{
    return (vec3){a.x -b.x, a.y-b.y, a.z-b.z};
}
vec3 vec3_mul(vec3 v, float amount)
{
    return (vec3){
        .x = v.x*amount,
        .y = v.y*amount,
        .z = v.z*amount
    };
}
vec3 vec3_div(vec3 a, float factor)
{
    return (vec3){a.x/factor, a.y/factor, a.z/factor};
}
vec3 vec3_cross(vec3 a, vec3 b)
{
    return (vec3){
        .x = a.y*b.z - a.z*b.y,
        .y = a.z*b.x - a.x*b.z,
        .z = a.x*b.y - a.y*b.x
    };
}



vec3 vec3_rotateZ(vec3 v, float angle)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    return (vec3){
        .x = v.x*cos_angle - v.y*sin_angle,
        .y = v.y*cos_angle + v.x*sin_angle,
        .z = v.z
    };
}

vec3 vec3_rotateY(vec3 v, float angle)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    return (vec3){
        .x = v.x*cos_angle - v.z*sin_angle,
        .y = v.y,
        .z = v.z*cos_angle + v.x*sin_angle
    };
}

vec3 vec3_rotateX(vec3 v, float angle)
{
    float cos_angle = cos(angle);
    float sin_angle = sin(angle);
    return (vec3){
        .x = v.x,
        .y = v.y*cos_angle - v.z*sin_angle,
        .z = v.z*cos_angle + v.y*sin_angle
    };
}


void vec3_debug(vec3 v)
{
    debug_start
        printf("Vec3 debug info:\n\tX: %f, Y: %f, Z: %f\n",
            v.x, v.y, v.z
        );
    debug_end
}