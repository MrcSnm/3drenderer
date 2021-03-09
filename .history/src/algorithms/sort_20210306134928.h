#ifndef SORT_H
#define SORT_H

#define byte_swap(a, b, size) do{\
char *_a_ = (char*)(a), *_b_ = (char*)(b);\
size_t _sz = size;\
do{\
char _temp = *_a_;\
*_a_++ = *_b_;\
*_b_++ = _temp;\
}while(_sz--)\
}while(0)


///Private implementation for not having to pass typesize
void _insert_sort_impl(void* arr, size_t arr_length, size_t typeSize, int (*comparison)(void* a, void * b))
{
    for(size_t i = 1; i < arr_length; i++)//Dont start from 0 because it needs to compare
    {
        if(comparison((&arr)[i], (&arr)[i-1]) < 0)
            byte_swap((&arr)[i], (&arr)[i-1], typeSize);
        
    }
}



#endif