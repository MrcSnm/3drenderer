#include "array.h"
#include "def.h"
#include <stdio.h>
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



void _Array_destroy_impl(void* arr)
{
    free((int*)arr-ARR_FIELDS);
}

void _Array_setField(void* arr, int field, int v)
{
    ((int*)arr-ARR_FIELDS)[field] = v;
}

void* New_Array(size_t typeSize, size_t reserveAmount)
{
    int* mem = malloc(sizeof(int)*3 + (typeSize)*reserveAmount);//Alloc space for size and capacity + typesize;
    mem[ARR_LENGTH] = 0;
    mem[ARR_CAPACITY] = reserveAmount;
    mem[ARR_STRIDE] = typeSize;
    return (void*)(mem+ARR_FIELDS);
}

void* _Array_push_impl(void* arr, void* v)
{
    int l = Array_length(arr);
    int s = Array_stride(arr);
    if(l >= Array_capacity(arr))
        arr = Array_resize(arr, l*2);
        
    memcpy((char*)arr+(l*s), v, s);

    _Array_setField(arr, ARR_LENGTH, l+1);
    return arr;
}

void* _Array_pop_impl(void* arr)
{
    int l = Array_length(arr);
    char* ret = &((char*)arr)[(l-1)*Array_stride(arr)];
    _Array_setField(arr, ARR_LENGTH, l-1);
    return ret;
}

int Array_stride(void* arr)
{
    return *((int*)arr-ARR_FIELDS+ARR_STRIDE);
}

int Array_length(void* arr)
{
    return *((int*)arr-ARR_FIELDS+ARR_LENGTH);
}

int Array_capacity(void* arr)
{
    return *((int*)arr-ARR_FIELDS+ARR_CAPACITY);
}


void* Array_resize(void* arr, size_t quant)
{
    void* ret = New_Array(Array_stride(arr), quant);
    memcpy(ret, arr, Array_length(arr)*Array_stride(arr));

    _Array_setField(ret, ARR_LENGTH, Array_length(arr));
    _Array_setField(ret, ARR_CAPACITY, quant);
    _Array_setField(ret, ARR_STRIDE, Array_stride(arr));

    // Array_debug(ret);
    Array_destroy(arr);
    return ret;
}

void* Array_reserve(void* arr, size_t quant)
{
    if(Array_capacity(arr) < quant)
        return Array_resize(arr, quant);
    return arr;
}

void Array_clear(void* arr)
{
    _Array_setField(arr, ARR_LENGTH, 0);
}

void Array_debug(void* arr)
{
    debug_start
        printf("Array debug info:\n\tUse: %d/%d, Stride: %d, Data: %p\n", 
            Array_length(arr), Array_capacity(arr), Array_stride(arr), arr
        );
    debug_end
}

void Array_print(char* formatChar, void* arr)
{
    char* a = arr;

    size_t stride = Array_stride(arr);
    for(int i = 0; i < Array_length(arr); i+= stride)
        printf(formatChar, a[i]);
    printf("\n");
}