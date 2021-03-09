#ifndef SORT_H
#define SORT_H


#define byte_swap(a, b, size) do{\
char *_a_ = (char*)(a), *_b_ = (char*)(b);\
size_t _sz = (size);\
do{\
char _temp = *_a_;\
*_a_++ = *_b_;\
*_b_++ = _temp;\
}while(--_sz);\
}while(0)


///Insert sort, pass a function that returns a number < 0 for ascending order, > 0 for descending
#define insert_sort(arr, length, func) _insert_sort_impl(arr, length, sizeof(arr[0]), func)
#define insert_sort_asc(arr, length, func) insert_sort(arr, length, sort_dsc_##typeName)
#define insert_sort_dsc(arr, length, typeName) insert_sort(arr, length, sort_asc_##typeName)


int sort_asc_int(void* a, void* b);
int sort_dsc_int(void* a, void* b);
int sort_asc_uint32_t(void* a, void* b);
int sort_dsc_uint32_t(void* a, void* b);
int sort_asc_size_t(void* a, void* b);
int sort_dsc_size_t(void* a, void* b);
int sort_asc_float(void* a, void* b);
int sort_dsc_float(void* a, void* b);
int sort_asc_double(void* a, void* b);
int sort_dsc_double(void* a, void* b);


///Private implementation for not having to pass typesize
void _insert_sort_impl(void* arr, size_t arr_length, size_t typeSize, int (*comparison)(void* a, void * b));

#endif