#include "vector.h"
#include <stdio.h>
#include <math.h>

inline vec2 vec2_add(vec2 a, vec2 b)
{
    return (vec2){a.x+b.x, a.y+b.y};
}
inline vec2 vec2_sub(vec2 a, vec2 b)
{
    return (vec2){a.x-b.x, a.y-b.y};
}
inline vec2 vec2_scale(vec2 a, float scale)
{
    return (vec2){a.x*scale, a.y*scale};
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

float vec2_mag(vec2 v)
{
    return sqrt(v.x*v.x+v.y*v.y);
}
float vec3_mag(vec3 v)
{
    return sqrt(v.x*v.x+v.y*v.y+v.z*v.z);
}


void vec3_debug(vec3 v)
{
    debug_start
        printf("Vec3 debug info:\n\tX: %f, Y: %f, Z: %f\n",
            v.x, v.y, v.z
        );
    debug_end
}