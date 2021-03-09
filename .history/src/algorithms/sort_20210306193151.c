#include "sort.h"
#include <stdint.h>
#include "../array.h"

int sort_asc_int(void* a, void* b){return *(int*)a - *(int*)b;}
int sort_dsc_int(void* a, void* b){return *(int*)b - *(int*)a;}
int sort_asc_uint32_t(void* a, void* b){return *(uint32_t*)a - *(uint32_t*)b;}
int sort_dsc_uint32_t(void* a, void* b){return *(uint32_t*)b - *(uint32_t*)a;}
int sort_asc_size_t(void* a, void* b){return *(size_t*)a - *(size_t*)b;}
int sort_dsc_size_t(void* a, void* b){return *(size_t*)b - *(size_t*)a;}
int sort_asc_float(void* a, void* b){return *(float*)a - *(float*)b;}
int sort_dsc_float(void* a, void* b){return *(float*)b - *(float*)a;}
int sort_asc_double(void* a, void* b){return *(double*)a - *(double*)b;}
int sort_dsc_double(void* a, void* b){return *(double*)b - *(double*)a;}

///Private implementation for not having to pass typesize
void _insert_sort_impl(void* arr, size_t arr_length, size_t typeSize, int (*comparison)(void* a, void * b))
{
    size_t sortedIndex = 0;
    char* a = (char*)arr;
    arr_length*=typeSize;

    for(size_t i = typeSize; i < arr_length; i+=typeSize)//Dont start from 0 because it needs to compare
    {
        sortedIndex = i;
        while(sortedIndex > 0 && comparison(&a[sortedIndex], &a[sortedIndex-typeSize]) < 0)
        {
            byte_swap(&a[sortedIndex], &a[sortedIndex-typeSize], typeSize);
            sortedIndex-=typeSize;
        }
    }
}