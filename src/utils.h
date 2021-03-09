#ifndef UTILS_H
#define UTILS_C
#include "def.h"

#define swap(a, b) do{\
typeof(a) tmp = b;\
b = a;\
a = tmp;\
}while(0)


int abs_i(int num);
float abs_f(float num);

#endif