#ifndef SORT_H
#define SORT_H

#define byte_swap(a, b, size) do{\
char* _a = (a), *_b = (b);\
do{\
char _temp = *_a;\
*_a++ = *_b;\
*_b++ = temp;\
}while(size--)\
}while(0)


// void insert_sort(void* arr, int length, int (*comparison)(void* a, void * b))
// {
//     qso
// }



#endif