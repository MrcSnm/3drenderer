#include "utils.h"

typedef struct Void Void;


void swap(void* a, void* b)
{
    void* temp = b;
    *(Void*)a = *(Void*)b;
    
}