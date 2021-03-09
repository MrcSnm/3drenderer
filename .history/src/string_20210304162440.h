#ifndef STRING_H
#define STRING_H

#include "def.h"
#include <stdlib.h>
#include <string.h>

class(String, {
    int length;
    char data[];
});

constructor(String, ARGS(char* content));
destructor(String, ARGS(String s));

long strCountLinebreaks(char* str);
#endif