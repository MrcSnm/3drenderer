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
    
    long length = fseek(f, 0L, SEEK_END);
    char* ret = malloc(length+1);
    




    fclose(f);
}