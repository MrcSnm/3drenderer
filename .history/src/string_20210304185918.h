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

bool strIsNumberChar(char c);
size_t strCountChars(char* str, char check);
size_t strCountCharsUntil(char* str, char check, size_t maxIterations);
#endif