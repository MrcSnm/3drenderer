#ifndef DEF_H
#define DEF_H

#include <stdbool.h>
#include <stdint.h>

#define null (void*)0

#ifdef RELEASE
    #define debug //
    #define debug_start /*
    #define debug_end */
#else
    #define debug
    #define debug_start
    #define debug_end
#endif

#define always_inline inline __attribute__((always_inline))

#ifndef typeof
#define typeof __typeof__
#endif

#define class(name, ...) typedef struct __VA_ARGS__ name##_; \
typedef name##_* name;

#define print(format, ...) printf(format, __VA_ARGS__)

///Creates arguments for a function
#define ARGS(...) (__VA_ARGS__)
///Creates a constructor for the type to be called with `new`
#define constructor(name, ...) name  New_##name __VA_ARGS__

///Calls constructor for `name` with args
#define new(name, ...) New_##name(__VA_ARGS__)

///Allocates memory for `sizeof(type)*size`
#define NEW(type, size)(type*)malloc(sizeof(type)*size)
///Allocates memory for `sizeof(type)*size`, and execute __VA_ARGS__ if it fails to allocate
#define SAFE_NEW(target, type, size, ...) NEW(type, size);\
if(!target){\
    __VA_ARGS__\
}

#define destroy(obj)\
Destroy_##typeof(obj);\
obj = null
#define destructor(name, ...) void Destroy_##name __VA_ARGS__

/**
 * Creates a for loop unrolled to finish with a quarter of iterations.
 * 
 * Params:
 *  max: when loop finishes(must be divisible by 4)
 * 
 * Use unroll_i to access current iteration
 */
#define for_unroll4(max, ...) \
for(int unroll_i = 0; unroll_i < max; unroll_i++) {\
    __VA_ARGS__;\
    unroll_i++;\
    __VA_ARGS__;\
    unroll_i++;\
    __VA_ARGS__;\
    unroll_i++;\
    __VA_ARGS__;\
}




#endif