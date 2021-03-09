#ifndef UTILS_H
#define UTILS_C

#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)

#define swap(a,b) do {typeof(a) _tmp_ = b; a = b; b = _tmp_;} while(0)


#endif