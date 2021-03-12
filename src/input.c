#include "input.h"
#include <stdio.h>
#include "def.h"


ubyte inputMap[256]= {0};
function(void, inputHandlers[256])(void) = {null};

static Uint32 last_wheel_move_ts = 0; 

bool Input_hasWheelMoved(SDL_MouseWheelEvent* ev)
{
    Uint32 ts = ev->timestamp;
    if(ts != last_wheel_move_ts && ev->y != 0)
    {
        last_wheel_move_ts = ts;
        return true;
    }
    return false;
}
extern inline bool Input_hasWheelMovedDown(SDL_MouseWheelEvent* ev);
extern inline bool Input_hasWheelMovedUp(SDL_MouseWheelEvent* ev);

void Input_enable(ubyte key)
{
    inputMap[key] = 1;
}
void Input_disable(ubyte key)
{
    inputMap[key] = 0;
}

bool Input_exec(ubyte key)
{
    inputHandlers[key]();
    return true;
}
void Input_setKeyHandler(ubyte key, function(void, cb)(void))
{
    if(key >= 'A' && key <= 'Z')
        key+= 'a' - 'A'; //Bring to lowercase
    inputHandlers[key] = cb;
}

void Input_update(void)
{
    for(ubyte i = 0; i < 255; i++)
    {
        if(inputHandlers[i] && inputMap[i])
            Input_exec(i);
    }
}
