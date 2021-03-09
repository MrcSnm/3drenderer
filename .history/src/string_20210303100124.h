#ifndef STRING_H
#define STRING_H

#include "def.h"
#include <stdlib.h>
#include <string.h>

class()
typedef struct string
{
    int length;
    char data[];
} string;

string String(char* content)
{
    int len = strlen(content);

    string s;
    s.length = len;


}

void String_destroy(string s)
{

}

#endif