#ifndef UTILS_H
#define UTILS_C

#define swap(a,b) do \
{ \
    typeof(a) _tmp_ = b;\
    a = b;\
    b = _tmp_;\
} while(0)


#endif