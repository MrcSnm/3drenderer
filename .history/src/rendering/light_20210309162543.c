#include "light.h"
#include "color.h"
#include "../triangle.h"


float light_flatShading(vec3 vA, vec3 vB, vec3 vC, vec3 lightDirection)
{
    vec3 normal = vec3_cross(vec3_sub(vB, vA), vec3_sub(vC, vA));
    vec3_normallize(&normal);
    return -vec3_dot(normal, lightDirection);
}