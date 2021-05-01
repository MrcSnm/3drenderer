#include "triangle.h"
#include "math/vector.h"



vec3 Triangle_getNormal(vec3 a, vec3 b, vec3 c)
{
    vec3 b_a = vec3_sub(b, a);
    vec3 c_a = vec3_sub(c, a);
    vec3 normal =  vec3_cross(b_a, c_a);
    vec3_normallize(&normal);
    return normal;
}