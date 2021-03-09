#include "def.h"

ubyte inputMap[255]= {0};
function(void, inputHandlers[255])(void);


void Input_setKeyHandler(ubyte key, function(void, cb)(void))
{
    inputMap[key] = 1;
    inputHandlers[key] = cb;
}