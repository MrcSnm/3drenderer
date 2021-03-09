#ifndef ARRAY_H
#define ARRAY_H

#define Array(T, size) &((T*)New_Array(sizeof(T), size))[2]
#define ARR_SIZE 3
#define ARR_OFFSET ARR_SIZE*sizeof(int)

#endif