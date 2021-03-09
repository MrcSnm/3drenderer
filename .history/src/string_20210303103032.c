#include "string.h"


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