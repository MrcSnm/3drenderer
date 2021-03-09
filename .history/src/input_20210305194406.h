#ifndef INPUT_H
#define INPUT_H

#include "def.h"

extern ubyte inputMap[255];
extern function(void, inputHandlers[255])(void);


bool Input_exec(ubyte key);
void Input_setKeyHandler(ubyte key, function(void, cb)(void));
#endif