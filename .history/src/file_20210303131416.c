#include "file.h"
#include <stdio.h>

bool File_exists(char* filename)
{
    FILE* f = fopen(filename, "r");
    bool ret = f != null;
    if(ret)
        fclose(f);
    return ret;
}

char* File_readText(char* filename)
{
    FILE* f = fopen(filename, "r");
    if(f == null)
        return "";
    
    fseek(f, 0L, SEEK_END);
    long length = ftell(f);
    rewind(f);
    char* ret = malloc(length+1);

    fread(ret, sizeof(char), length, f);
    ret[length+1] = '\0';
    fclose(f);

    
    return ret;
}