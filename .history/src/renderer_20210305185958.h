#ifndef RENDERER_H
#define RENDERER_H
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "def.h"


#define FPS 60
#define FRAME_MS (1000/FPS)
enum PX_STATES
{
    PX_STATES_VERTEX = 1,
    PX_STATES_WIREFRAME = 1<<1,
    PX_STATES_FILL = 1 << 2,
    PX_STATES_BACKFACE_CULLING = 1 << 3
};

typedef struct PXRenderer
{
    uint32_t state;
} PXRenderer;

typedef struct PixelBuffer
{
    SDL_Texture* texture;
    uint32_t* data;
    int width, height, halfW, halfH;
    uint32_t length;
} PixelBuffer;


extern PXRenderer pxRenderer;
extern PixelBuffer pxBuffer;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Surface* surface;
extern int window_width;
extern int window_height;


///Use PX_STATE enum for building the state
void PXRenderer_setState(uint32_t state);
///Checks wether the renderer has got the target state from PX_STATE
#define PXRenderer_has(STATE) ((pxRenderer.state & STATE) == 1)
void pxStart(void);
bool initialize_window(void);
void pxClear(uint32_t color);
void pxRender(void);
void pxFillRect(int x, int y, int width, int height, uint32_t color);
void pxFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void pxDrawLine(int x0, int y0, int x1, int y1, uint32_t color);
void pxDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void pxDrawGrid(int color, int xOffset, int yOffset);

void pxDestroy(void);


/**
 * Unsafely draws a pixel given a linear position, no checks are performed, no multiplication either.
 * This function is useful for when iterating through X with constant Y, so it spares the multiplication
 */
always_inline void pxDrawPixelU(int pos, uint32_t color)
{
    pxBuffer.data[pos] = color;
}

///Unsafely draws a pixel given X and Y, no checks are perfomed, useful for managed primitives
always_inline void pxDrawPixelUXY(int x, int y, uint32_t color)
{
    pxDrawPixelU(x+y*pxBuffer.width, color);
}

///Safely draws a pixel clipping it if needed
always_inline void pxDrawPixel(int x, int y, uint32_t color)
{
    if(x>= 0 && x < pxBuffer.width && y >= 0 && y < pxBuffer.height)
        pxDrawPixelUXY(x, y, color);
}

#endif