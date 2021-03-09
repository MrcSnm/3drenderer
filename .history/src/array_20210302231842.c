#include "array.h"
#include "stdlib.h"

/**
 * Creates an array in this data layout, but abstracts size and capacity for being
 * able to create an array accessible with index operator
```c
struct Array
{
    int size;
    int capacity;
    void* data;
}
```
*/


void* New_Array(size_t typeSize, size_t reserveAmount)
{
    void* mem = malloc(sizeof(int)*2 + (typeSize)*reserveAmount);//Alloc space for size and capacity + typesize;
    (int*)mem[1] = reserveAmount;
    return mem;
}

void 