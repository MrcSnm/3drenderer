#ifndef DEF_H
#define DEF_H

#include <stdbool.h>
#include <stdint.h>


/////////////////////////////////////////////////////////////////////
// Type definitions from D
/////////////////////////////////////////////////////////////////////
typedef char byte;
typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

/////////////////////////////////////////////////////////////////////
// D Keywords
/////////////////////////////////////////////////////////////////////
#define out(type) type*
#define null (void*)0
#ifndef typeof
#define typeof __typeof__
#endif

///Creates a callback type, append () to set arguments
#define function(retType, cbName) retType (*cbName)

#define class(name, ...) typedef struct __VA_ARGS__ name##_; \
typedef name##_* name;

///Calls constructor for `name` with args
#define new(name, ...) New_##name(__VA_ARGS__)
///Calls destructor and set it to null, no extra args are received
#define destroy(type, obj)\
Destroy_##type(obj);\
obj = null


/////////////////////////////////////////////////////////////////////
// Backing functions for call new and destroy
/////////////////////////////////////////////////////////////////////

///Creates a constructor for the type to be called with `new`
#define constructor(name, ...) name  New_##name __VA_ARGS__
///Creates a constructor for the type to be called with `destroy`
#define destructor(name, ...) void Destroy_##name __VA_ARGS__


/////////////////////////////////////////////////////////////////////
// Macro Processing
/////////////////////////////////////////////////////////////////////

///Creates arguments for a function
#define ARGS(...) (__VA_ARGS__)
#define PASTE(arg) arg


/////////////////////////////////////////////////////////////////////
// Debugging
/////////////////////////////////////////////////////////////////////

#ifdef RELEASE
    #define debug if(0)
    #define debug_start if(0){
    #define debug_end }
#else
    #define debug if(1)
    #define debug_start if(1){
    #define debug_end }
#endif

#define print(format, ...) printf(__FILE__":%d " format, __LINE__, __VA_ARGS__)
#define println(format, ...) print(format "\n", __VA_ARGS__)
///Prints a char and jump line
#define println_c(v) print("%c\n", v)
///Prints a integer and jump line
#define println_d(v) print("%d\n", v)
///Prints a float and jump line
#define println_f(v) print("%f\n", v)

/////////////////////////////////////////////////////////////////////
// Optimization and profiling
/////////////////////////////////////////////////////////////////////
#define always_inline inline __attribute__((always_inline))

#ifndef RELEASE

///Put it on file top to define the static clock
#define profiling_static static clock_t _prof_begin_st, _prof_end_st;
///Start profiling on static clock
#define profiling_static_start _prof_begin_st = clock();
///End profiling the static clock
#define profiling_static_end(name) _prof_end_st = clock(); \
print("Time spent on %s: %lf secs\n", name, (double)(_prof_end_st - _prof_begin_st)/CLOCKS_PER_SEC);


#define profiling_start {  \
clock_t _prof_begin, _prof_end;\
_prof_begin = clock();

#define profiling_end(name) _prof_end = clock(); \
print("Time spent on %s: %lf secs\n", name, (double)(_prof_end - _prof_begin)/CLOCKS_PER_SEC);\
}
#else
#define profiling_static
#define profiling_static_start
#define profiling_static_end(name)
#define profiling_start
#define profiling_end(name)
#endif

/////////////////////////////////////////////////////////////////////
// Snippets
/////////////////////////////////////////////////////////////////////

///Allocates memory for `sizeof(type)*size`
#define NEW(type, size)(type*)malloc(sizeof(type)*size)
///Allocates memory for `sizeof(type)*size`, and execute __VA_ARGS__ if it fails to allocate
#define SAFE_NEW(target, type, size, ...) NEW(type, size);\
if(!target){\
    __VA_ARGS__\
}


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