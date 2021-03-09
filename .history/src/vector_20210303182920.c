#include "vector.h"
#include <math.h>


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
        printf("Vec3 debug info:\n\tX: %f, Y: %f, Z: %f",
            v.x, v.y, v.z
        );
    debug_end
}