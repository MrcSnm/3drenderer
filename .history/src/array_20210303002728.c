#include "array.h"
#include <stdlib.h>
#include <string.h>

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
    int* mem = malloc(sizeof(int)*2 + (typeSize)*reserveAmount);//Alloc space for size and capacity + typesize;
    ((int*)mem)[0] = 0;
    ((int*)mem)[1] = reserveAmount;
    ((int*)mem)[2] = typeSize;
    return (void*)(mem+ARR_SIZE);
}

void Array_push(void* arr, void* v)
{
    int l = Array_length(arr);
    int s = Array_stride(arr);
    if(l == Array_capacity(arr))
    {
        
    }
    memcpy((char*)arr+(l*s), v, s);
}

int Array_stride(void* arr)
{
    return ((int*)arr) + ARR_STRIDE;
}

int Array_length(void* arr)
{
    return ((int*)arr) + ARR_LENGTH;
}

int Array_capacity(void* arr)
{
    return ((int*)arr) + ARR_CAPACITY;
}


void* Array_resize(void* arr, size_t quant)
{
    int capacity = Array_capacity(arr);
    void* ret = New_Array(Array_stride(arr), quant);
    memcpy(ret, arr, Array_length(arr)*Array_stride(arr));
    Array_destroy(arr);
    return ret;
}

void Array_reserve(void** arr, size_t quant)
{
    if(Array_capacity(arr) < quant)
        *arr = Array_resize(*arr, quant);
}

void Array_destroy(void* arr)
{
    free((int*)arr-ARR_OFFSET);
}