#ifndef SORT_H
#define SORT_H

#define byte_swap(a, b, size) do{\
char* _temp = (char*)a;int i = 0;\
do{\
((char*)b)[i] = _temp\
}while(size--)\
}while(0)

// void insert_sort(void* arr, int length, int (*comparison)(void* a, void * b))
// {
//     qso
// }



#endif