#ifndef ARRAY_H
#define ARRAY_H

#define Array(T, size) &((T*)New_Array(sizeof(T), size))[2]

#define ARR_LENGTH 0
#define ARR_CAPACITY 1
#define ARR_STRIDE 2

#define ARR_FIELDS 3



void* New_Array(size_t typeSize, size_t reserveAmount);
void* Array_push(void* arr, void* v);
void* Array_pop(void* arr);
int Array_stride(void* arr);
int Array_length(void* arr);

#endif