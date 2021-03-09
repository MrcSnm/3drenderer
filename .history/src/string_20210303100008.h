#ifndef STRING_H
#define STRING_H

#include <stdlib.h>
#include <string.h>


typedef struct string
{
    int length;
    char data[];
} string;

string String(char* content)
{
    int len = strnlen(content);
}

void String_destroy(string s)
{

}

#endif