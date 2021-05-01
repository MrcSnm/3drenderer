#ifndef RENDERER_H
#define RENDERER_H
#include "texture.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "../def.h"
#include "../math/vector.h"


#define FPS 60
#define FRAME_MS (1000/FPS)
enum PX_STATES
{
    PX_STATES_VERTEX = 1,
    PX_STATES_LINE = 1<<1,
    PX_STATES_FILL = 1 << 2,
    PX_STATES_TEXTURE = 1 << 3,
};

enum PX_CULL
{
    PX_CULL_NONE = 0,
    PX_CULL_BACK,
    PX_CULL_FRONT
};

typedef struct PXRenderer
{
    uint32_t drawStates;
    short cullType;
} PXRenderer;

typedef struct PixelBuffer
{
    SDL_Texture* texture;
    uint32_t* data;
    float* z_buffer;
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
void PXRenderer_setState(uint32_t PX_STATES);
void PXRenderer_setCulling(short PX_CULL);
///Checks wether the renderer has got the target state from PX_STATE
#define PXRenderer_has(STATE) ((pxRenderer.drawStates & STATE) != 0)
void pxStart(void);
bool initialize_window(void);
void pxClear(uint32_t color);
void pxClearZBuffer(void);
void pxRender(void);
void pxFillRect(int x, int y, int width, int height, uint32_t color);
void pxFillTriangle(int x0, int y0, float z0, float w0, int x1, int y1, float z1, float w1, int x2, int y2, float z2, float w2, uint32_t color);
void pxTextureTriangle(int x0, int y0, float z0, float w0, tex2D uvA, int x1, int y1, float z1, float w1, tex2D uvB, int x2, int y2, float z2, float w2, tex2D uvC, uint32_t color, Image* texture);
void pxDrawLine(int x0, int y0, int x1, int y1, uint32_t color);
void pxDrawTrianglePixel(int x, int y, uint32_t color, vec4 pA, vec4 pB, vec4 pC);
void pxDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color);
void pxDrawGrid(int color, int xOffset, int yOffset);

void pxDestroy(void);
void pxDrawTexel(int x, int y, Image* texture,
vec4 pA, tex2D uvA,
vec4 pB, tex2D uvB,
vec4 pC, tex2D uvC);

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
    pxDrawPixelU(x+(y*pxBuffer.width), color);
}

///Safely draws a pixel clipping it if needed
always_inline void pxDrawPixel(int x, int y, uint32_t color)
{
    if(x < 0 || x >= pxBuffer.width || y < 0 || y >= pxBuffer.height)
        return;
    pxDrawPixelUXY(x, y, color);
}


#endif