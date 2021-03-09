#ifndef SORT_H
#define SORT_H

#define byte_swap(a, b, size) do{\
char *_a_ = (a), *_b_ = (b);\
do{\
char _temp = *_a_;\
*_a_++ = *_b_;\
*_b_++ = _temp;\
}while(size--)\
}while(0)


void insert_sort_impl(void* arr, size_t arr_length, int (*comparison)(void* a, void * b))
{
    
}



#endif