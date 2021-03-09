#include "utils.h"


void swap_i(int* a, int* b)
{
    int* tmp = b;
    *b = *a;
    *a = *tmp;
}
void swap_f(float* a, float* b)
{
    float* tmp = b;
    *b = *a;
    *a = *tmp;
}
int abs_i(int num)
{
    if(num<0)
        num*=-1;
    return num;
}
float abs_f(float num)
{
    if(num<0)
        num*=-1;
    return num;
}