#include "def.h"
#include <SDL2/SDL.h>

ubyte inputMap[256]= {0};
function(void, inputHandlers[256])(void) = {null};



bool Input_hasWheelMovedDown(SDL_MouseWheelEvent* ev)
{
    return 
}


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
        key+= 'a' - 'A'; //Bring to lowercase
    inputMap[key] = 1;
    inputHandlers[key] = cb;
}