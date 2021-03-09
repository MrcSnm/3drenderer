#include "matrix.h"

mat4 mat4_identity(void)
{
    return (mat4)
    {
        {1, 0, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    };
}