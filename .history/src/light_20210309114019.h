#ifndef LIGHT_H
#define LIGHT_H
#include "math/vector.h"

typedef struct global_light
{
    vec3 direction;
} global_light;

float light_flatShading(vec3 faceNormal, vec3 lightDirection);

#endif