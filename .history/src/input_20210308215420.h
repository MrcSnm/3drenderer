#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
#include "def.h"

extern ubyte inputMap[256];
extern function(void, inputHandlers[256])(void);


inline bool Input_hasWheelMovedDown(SDL_MouseWheelEvent* ev)
{
    return ev->y == -1;
}
inline bool Input_hasWheelMovedUp(SDL_MouseWheelEvent* ev)
{
    return ev->y == 1;
}
bool Input_exec(ubyte key);
void Input_setKeyHandler(ubyte key, function(void, cb)(void));
#endif