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


void* New_Array(size_t typeSize, int reserveAmount)
{
    
}