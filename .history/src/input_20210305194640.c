#include "def.h"

ubyte inputMap[255]= {0};
function(void, inputHandlers[255])(void) = {null};


bool Input_exec(ubyte key)
{
    if(inputMap[key])
    {
        inputHandlers[key]();
        return true;
    }
    return false;
}
void Input_setKeyHandler(ubyte key, function(void, cb)(void))
{
    if(key >= 'A' && key <= 'Z')
        key+= 'Z' - 'A';
    inputMap[key] = 1;
    inputHandlers[key] = cb;
}