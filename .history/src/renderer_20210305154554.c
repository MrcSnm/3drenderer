#include "renderer.h"
#include "utils.h"
#include "math.h"

PixelBuffer pxBuffer;
SDL_Window* window = null;
SDL_Renderer* renderer = null;
SDL_Surface* surface = null;
int window_width = 800;
int window_height = 600;

// extern always_inline void pxDrawPixelU(int pos, uint32_t color);
// extern always_inline void pxDrawPixelUXY(int x, int y, uint32_t color);
// extern always_inline void pxDrawPixel(int x, int y, uint32_t color);

void pxStart(void)
{
    pxBuffer.length = window_width*(window_height+1);
    pxBuffer.width = window_width;
    pxBuffer.halfW = window_width/2;
    pxBuffer.halfH = window_height/2;
    pxBuffer.height = window_height;
    pxBuffer.data = SAFE_NEW(pxBuffer.data, uint32_t, pxBuffer.length, 
        printf("Could not allocate enough memory for pixelbuffer");
        return;
    );
    pxBuffer.texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_ARGB8888,
    SDL_TEXTUREACCESS_STREAMING,
    pxBuffer.width, pxBuffer.height);

}
bool initialize_window(void)
{
    if(SDL_Init(
        SDL_INIT_AUDIO|
        SDL_INIT_EVENTS|
        SDL_INIT_GAMECONTROLLER|
        SDL_INIT_VIDEO |
        SDL_INIT_TIMER
    ) != 0)//Err
    {
        fprintf(stderr, "Error intializing SDL\n");
        return false;
    }

    SDL_DisplayMode mode;
    SDL_GetCurrentDisplayMode(0, &mode);
    window_width = mode.w;
    window_height = mode.h;


    window = SDL_CreateWindow(
        null,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width,
        window_height,
        0
    );

    if(!window)
    {
        fprintf(stderr, "Error crating SDL window\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer)
    {
        fprintf(stderr, "Error crating SDL renderer\n");
        return false;
    }

    // surface = SDL_GetWindowSurface(window);
    return true;
}


///Receives the color in the ARGB8888 format
void pxClear(uint32_t color)
{
    for_unroll4(pxBuffer.length,
        pxBuffer.data[unroll_i] = color;
    );
}

void pxDrawGrid(int color, int xOffset, int yOffset)
{
    int x, y;
    int w = pxBuffer.width;
    int h = pxBuffer.height;

    //Manage rows
    for(y = 0; y< h; y+= yOffset)
    {
        int currentY = y*w;//Multiply once
        for_unroll4(w,
            pxBuffer.data[unroll_i+currentY] = color;
        )
    }


    //Manage columns
    for(x = 0; x< w; x+= xOffset)
    {
        for_unroll4(h,
            pxBuffer.data[unroll_i*w+x] = color;
        )
    }
}

void pxFillRect(int x, int y, int width, int height, uint32_t color)
{
    if(x+width<0 || y+height < 0) //Cut negative positions as there will never be overlap
        return;
    //Handle negative widths and heights
    if(width < 0)
    {
        x = x+width;
        width = -width;
    }
    if(height < 0)
    {
        y = y+height;
        height = -height;
    }
    //Handle overflow positions
    if(x > pxBuffer.width || y > pxBuffer.height)
        return;
    
    //Now clamp the rect to the visible part
    if(x<0)
    {
        width+= x;
        x = 0;
    }
    if(y<0)
    {
        height+= y;
        y = 0;
    }
    if(x+width>pxBuffer.width)
        width = (width-(x+width)%pxBuffer.width);
    if(y+height>pxBuffer.height)
        height = height-((y+height)%pxBuffer.height);

    int i;
    int currentY;
    int yEnd = height+y;
    int xEnd = width+x;


    for(;y < yEnd; y++)
    {
        currentY = y*pxBuffer.width;
        for(i = x; i < xEnd; i++)
            pxDrawPixelU(currentY+i, color);
    }
}

void pxFillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    //Sort Y, y2 > y1 > y0
    if(y0 > y1)
    {
        swap(y1, y0);
        swap(x1, x0);
    }
    if(y1 > y2)
    {
        swap(y2, y1);
        swap(x2, x1);
    }
    if(y0 > y1)
    {
        swap(y0, y1);
        swap(x0, x1);
    }

    //Draw flat_bot

    //Draw flat_top
}

void pxDrawLine(int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = x1-x0;
    int dy = y1-y0;

    int biggestSide = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

    float incX = dx /(float)biggestSide;
    float incY = dy /(float)biggestSide;
    //One of the incs are == 1

    float x = x0,y = y0;
    for(int i = 0; i <= biggestSide; i++)
    {
        pxDrawPixel(roundf(x), roundf(y), color);
        x+= incX;
        y+= incY;
    }


}

void pxDrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t color)
{
    pxDrawLine(x0, y0, x1, y1, color);
    pxDrawLine(x1, y1, x2, y2, color);
    pxDrawLine(x2, y2, x0, y0, color);
}



void pxRender(void)
{
    SDL_UpdateTexture(pxBuffer.texture,
        null,
        pxBuffer.data,
        (int)(sizeof(uint32_t) * pxBuffer.width)
    );

    SDL_RenderCopy(renderer, pxBuffer.texture, null, null);
}

void pxDestroy(void)
{
    free(pxBuffer.data);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
