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

    String s = malloc(sizeof(String_)+len);
    s->length = len;


});

destructor(String, ARGS(void)
{

});

#endif