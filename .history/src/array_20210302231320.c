#include "array.h"

struct Array
{
    int size;
    int capacity;
    void* data;
}


void* New_Array()