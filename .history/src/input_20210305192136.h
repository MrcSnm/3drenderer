#ifndef INPUT_H
#define INPUT_H

#include "def.h"

extern ubyte inputMap[255];
extern function(void, inputHandlers[255])(void);



void Input_setInputHandler(ubyte key, function(void, cb)(void));
#endif