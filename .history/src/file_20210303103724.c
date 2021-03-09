#include "file.h"
#include <stdio.h>

bool File_exists(char* filename)
{
    FILE* f = fopen(filename, "r");
    bool ret = f != null;
    
}

String File_readText(char* filename)
{
    
}