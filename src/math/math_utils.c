#include "math_utils.h"


float lerp(float p1, float p2, float t)
{
    return (1-t)*p1 + p2*t;
}