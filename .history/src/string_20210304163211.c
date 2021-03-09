#include "string.h"
#include <stdio.h>


constructor(String, ARGS(char* content)
{
    int len = strlen(content);
    String s = (String)malloc(sizeof(String_)+len);
    s->length = len;
    memcpy(s->data, content, len);

    return s;
});

destructor(String, ARGS(String s)
{
    free(s);
});

size_t strCountChars(char* str, char check)
{
    for(size_t i = 0, c = 0; str[i] != '\0'; i++)
        if(str[i] == check)c++;
    return check;
}
size_t strCountCharsUntil(char* str, char check, size_t maxIterations)
{
    for(size_t i = 0, c = 0; str[i] != '\0' || i >= maxIterations; i++)
        if(str[i] == check)c++;
    return check;   
}