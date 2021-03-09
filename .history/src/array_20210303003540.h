#ifndef ARRAY_H
#define ARRAY_H

#define Array(T, size) &((T*)New_Array(sizeof(T), size))[2]

#define ARR_LENGTH 0
#define ARR_CAPACITY 1
#define ARR_STRIDE 2

#define ARR_FIELDS 3

#endif