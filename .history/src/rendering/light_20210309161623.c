#include "light.h"
#include "../triangle.h"


float light_flatShading(vec3 vA, vec3 vB, vec3 vC, vec3 lightDirection, uint32_t color)
{
    vec3 normal = vec3_cross(vec3_sub(vB, vA), vec3_sub(vC, vA));
    vec3_normallize(&normal);
    float intensity = vec3_dot(normal, lightDirection);
    
}