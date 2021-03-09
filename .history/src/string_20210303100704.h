#ifndef STRING_H
#define STRING_H

#include "def.h"
#include <stdlib.h>
#include <string.h>

class(String, {
    int length;
    char data[];
});

constructor(String, ARGS(char* content)
{
    int len = strlen(content);

    String s = (String)malloc(sizeof(String_)+len);
    s->length = len;
    memcpy(s->data, content, len);


});

destructor(String, ARGS(void)
{

});

#endif