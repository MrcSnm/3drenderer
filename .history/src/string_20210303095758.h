#ifndef STRING_H
#define STRING_H


typedef struct string
{
    int length;
    char data[];
} string;

#endif