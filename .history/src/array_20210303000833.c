#include "array.h"
#include "stdlib.h"

/**
 * Creates an array in this data layout, but abstracts size and capacity for being
 * able to create an array accessible with index operator
```c
struct Array
{
    int size;
    int capacity;
    void* data;
}
```
*/


void* New_Array(size_t typeSize, size_t reserveAmount)
{
    void* mem = malloc(sizeof(int)*2 + (typeSize)*reserveAmount);//Alloc space for size and capacity + typesize;
    ((int*)mem)[0] = 0;
    ((int*)mem)[1] = reserveAmount;
    return mem;
}


int Array_length(void* arr)
{
    return ((int*)arr)-2;
}

int Array_capacity(void* arr)
{
    return ((int*)arr)-1;
}


void Array_reserve(void* arr, size_t quant)
{
    int capacity = Array_capacity(arr);
    if(capacity < quant)
    {
        ((int*)arr) = realloc(arr-2, quant+sizeof(int)*2);
        *(int*)(arr-1) = quant;
    }
}
