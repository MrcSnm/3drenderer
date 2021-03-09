extern ubyte inputMap[255];
extern function(void, inputHandlers[255])(void);



void Input_setKeyHandler(ubyte key, function(void, cb)(void));