#ifndef STRING_H
#define STRING_H

#include <stdlib.h>


typedef struct string
{
    int length;
    char data[];
} string;

string String(char* content)
{

}

void String_destroy(string s)
{

}

#endif