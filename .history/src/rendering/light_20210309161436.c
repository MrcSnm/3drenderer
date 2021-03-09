#include "light.h"
#include "../triangle.h"


float light_flatShading(face_t face, vec3 lightDirection)
{

    return vec3_dot(faceNormal, lightDirection);
}