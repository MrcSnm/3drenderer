#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>


#define ARR_LENGTH 0
#define ARR_CAPACITY 1
#define ARR_STRIDE 2
#define ARR_FIELDS 3
#define Array(T, size) ((T*)New_Array(sizeof(T), size))


#define Array_push(arr, v) do{\
__typeof__(v) _temp_ = v;\
arr = _Array_push_impl(arr, &_temp_);\
}while(0)
#define Array_destroy(arr) _Array_destroy_impl(arr); arr = NULL
#define Array_pop(arr) *(__typeof__(arr))_Array_pop_impl(arr)



void _Array_setField(void* arr, int field, int v);
void _Array_destroy_impl(void* arr);
void* New_Array(size_t typeSize, size_t reserveAmount);
void* _Array_push_impl(void* arr, void* v);
void* _Array_pop_impl(void* arr);
int Array_stride(void* arr);
int Array_length(void* arr);
int Array_capacity(void* arr);
void* Array_resize(void* arr, size_t quant);
void Array_reserve(void** arr, size_t quant);

#endif