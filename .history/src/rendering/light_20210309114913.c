#include "light.h"


float light_flatShading(vec3 faceNormal, vec3 lightDirection)
{
    return vec3_dot(faceNormal, lightDirection);
}