#ifndef ARRAY_H
#define ARRAY_H

#define Array(T, size) &((T*)New_Array(sizeof(T), size))[2]
#define ARR_SIZE 2 * sizeof(int)

#endif