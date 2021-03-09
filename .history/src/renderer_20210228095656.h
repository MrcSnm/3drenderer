#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "def.h"


typedef struct PixelBuffer
{
    SDL_Texture* texture;
    uint32_t* data;
    int width, height;
    uint32_t length;
} PixelBuffer;


extern PixelBuffer pxBuffer;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Surface* surface;
extern int window_width;
extern int window_height;

void pxStart(void);
bool initialize_window(void);
void pxClear(uint32_t color);
void pxRender(void);
void pxFillRect(int x, int y, int width, int height, uint32_t color);
void pxDrawGrid(int color, int xOffset, int yOffset);

void pxDestroy(void);
inline void pxDrawPixel(int x, int y, uint32_t color)
{
    if(x < pxBuffer.width || y < pxBuffer.height)
        pxBuffer.data[x+y*pxBuffer.width] = color;
}

#endif