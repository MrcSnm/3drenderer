#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>


#define ARR_LENGTH 0
#define ARR_CAPACITY 1
#define ARR_STRIDE 2
#define ARR_FIELDS 3
#define Array(T, size) ((T*)New_Array(sizeof(T), size))


#define Array_pushv(arr, v) do{__typeof__(v) _temp_ = v;Array_push(arr, &_temp_);}while(0);



void _Array_setField(void* arr, int field, int v);
void Array_destroy(void* arr);
void* New_Array(size_t typeSize, size_t reserveAmount);
void* Array_push(void* arr, void* v);
void* Array_pop(void* arr);
int Array_stride(void* arr);
int Array_length(void* arr);
int Array_capacity(void* arr);
void* Array_resize(void* arr, size_t quant);
void Array_reserve(void** arr, size_t quant);

#endif