#include "utils.h"

void swap_i(int* a, int* b)
{
    int* tmp = b;
    *b = *a;
    *a = *tmp;
}
void swap_f(float* a, float* b);
int abs_i(int num);
float abs_f(float num);