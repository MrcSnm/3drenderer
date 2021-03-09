#include "sort.h"

#include <stdint.h>

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