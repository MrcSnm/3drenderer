#ifndef LIGHT_H
#define LIGHT_H
#include "../math/vector.h"

typedef struct global_light
{
    vec3 direction;
} global_light;

/**
 * Gets a triangle's face vertices
 * Calculates its normal
 * Returns the lighting rate.
 */
float light_flatShading(vec3 vA, vec3 vB, vec3 vC, vec3 lightDirection, uint32_t color);

#endif