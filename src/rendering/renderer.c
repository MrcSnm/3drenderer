#include "renderer.h"
#include <string.h>
#include "../math/vector.h"
#include "../math/math_utils.h"
#include "../utils.h"
#include "math.h"

PXRenderer pxRenderer;
PixelBuffer pxBuffer;
SDL_Window* window = null;
SDL_Renderer* renderer = null;
SDL_Surface* surface = null;
int window_width = 320;
int window_height = 200;

// extern always_inline void pxDrawPixelU(int pos, uint32_t color);
// extern always_inline void pxDrawPixelUXY(int x, int y, uint32_t color);
// extern always_inline void pxDrawPixel(int x, int y, uint32_t color);

void PXRenderer_setState(uint32_t PX_STATES)
{
    pxRenderer.drawStates = PX_STATES;
}
void PXRenderer_setCulling(short PX_CULL)
{
    switch (PX_CULL)
    {
    case PX_CULL_BACK:
    case PX_CULL_FRONT:
    case PX_CULL_NONE:
        pxRenderer.cullType = PX_CULL;
        break;
    default:
        print("Unknown culling type %d", PX_CULL);
        exit(EXIT_FAILURE);
        break;
    }
}
void pxStart(void)
{
    pxBuffer.length = window_width*(window_height+1);
    pxBuffer.width = window_width;
    pxBuffer.halfH = window_height/2;
    pxBuffer.height = window_height;
    pxBuffer.halfW = window_width/2;
    pxBuffer.data = SAFE_NEW(pxBuffer.data, uint32_t, pxBuffer.length, 
        printf("Could not allocate enough memory for pixelbuffer");
        return;
    );
    pxBuffer.z_buffer = SAFE_NEW(pxBuffer.z_buffer, float, pxBuffer.length, 
        printf("Could not allocate enough memory for z buffer");
        return;
    );
    pxBuffer.texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGBA32,
    SDL_TEXTUREACCESS_STREAMING,
    pxBuffer.width, pxBuffer.height);

    PXRenderer_setState(PX_STATES_TEXTURE);
    PXRenderer_setCulling(PX_CULL_BACK);
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
    int fullscreen_width = mode.w;
    int fullscreen_height =  mode.h;


    window = SDL_CreateWindow(
        null,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        fullscreen_width,
        fullscreen_height,
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
void pxClearZBuffer(void)
{
    for_unroll4(pxBuffer.length, 
        pxBuffer.z_buffer[unroll_i] = 1.0f;
    )
    // memset(pxBuffer.z_buffer, 1, pxBuffer.length);
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

void pxDrawTrianglePixel(int x, int y, uint32_t color,
vec4 pA, vec4 pB, vec4 pC)
{
    vec2 a = vec2_from_vec4(pA);
    vec2 b = vec2_from_vec4(pB);
    vec2 c = vec2_from_vec4(pC);
    vec3 weights = barycentric_weights(a, b, c, (vec2){x, y});

    float alpha = weights.x;
    float beta = weights.y;
    float gamma = weights.z;
    alpha = fmax(0, alpha);
    beta = fmax(0, beta);
    gamma = fmax(0, gamma);
    

    //Applying Old Z (W) to correct perspective
    float rep_aw = 1/pA.w;
    float rep_bw = 1/pB.w;
    float rep_cw = 1/pC.w;

    float w_reciprocal = (rep_aw*alpha) + (rep_bw*beta) + (rep_cw*gamma);

    //Transform 1/w into w/1 
    //Make the closer values have smaller values
    w_reciprocal = 1.0f - w_reciprocal;

    //Only draw the pixel if the depth value is less than the previously stored
    if(w_reciprocal < pxBuffer.z_buffer[y*pxBuffer.width+x])
    {
        pxDrawPixel(x, y, color);
        //Saves into the z_buffer w_recriprocal
        pxBuffer.z_buffer[y*pxBuffer.width + x] = w_reciprocal;
    }
}

void pxFillTriangle(
int x0, int y0, float z0, float w0,
int x1, int y1, float z1, float w1,
int x2, int y2, float z2, float w2,
uint32_t color)
{
    //Sort Y, y2 > y1 > y0
    if(y0 > y1)
    {
        swap(z1, z0);
        swap(w1, w0);
        swap(y1, y0);
        swap(x1, x0);
    }
    if(y1 > y2)
    {
        swap(y2, y1);
        swap(x2, x1);
        swap(z2, z1);
        swap(w2, w1);
    }
    if(y0 > y1)
    {
        swap(y0, y1);
        swap(x0, x1);
        swap(z0, z1);
        swap(w0, w1);
    }

    //Finding middle x and y using trinagle similarity
    //int my = y1; (Dont do it on release)    

    float inv_slope1 = 0;
    float inv_slope2 = 0;
    int dy1 = abs(y1-y0), dy2 = abs(y2-y0);

    if(dy1)
        inv_slope1 = (float)(x1-x0)/dy1;
    if(dy2)
        inv_slope2 = (float)(x2-x0)/dy2;

    int x_start,x_end;

    vec4 pA = {x0, y0, z0, w0};
    vec4 pB = {x1, y1, z1, w1};
    vec4 pC = {x2, y2, z2, w2};

    if(y0-y1 != 0)
    {
        for(int y = y0; y <= y1; y++)
        {
            x_start = x1 + (y - y1)*inv_slope1;
            x_end =   x0 + (y - y0)*inv_slope2;

            if(x_start > x_end)
                swap(x_start, x_end);

            while(x_start <= x_end)
            {
                pxDrawTrianglePixel(x_start, y, color, pA, pB, pC);
                x_start++;
            }
        }
    }

    dy1 = abs(y2-y1);
    dy2 = abs(y2-y0);

    if(dy1)
        inv_slope1 = (float)(x2-x1)/dy1;
    if(dy2)
        inv_slope2 = (float)(x2-x0)/dy2;

    if(y1-y2 != 0)
    {
        for(int y = y1; y <= y2; y++)
        {
            x_start = x1 + (y-y1)*inv_slope1;
            x_end = x2 + (y-y2)*inv_slope2;
            if(x_start > x_end)
                swap(x_start, x_end);

            while(x_start < x_end)
            {
                pxDrawTrianglePixel(x_start, y, color, pA, pB, pC);
                x_start++;
            }
        }
    }

}

void pxDrawTexel(int x, int y, Image* image,
vec4 pA, tex2D uvA,
vec4 pB, tex2D uvB,
vec4 pC, tex2D uvC)
{
    vec2 a = vec2_from_vec4(pA);
    vec2 b = vec2_from_vec4(pB);
    vec2 c = vec2_from_vec4(pC);
    vec3 weights = barycentric_weights(a, b, c, (vec2){x, y});

    float alpha = weights.x;
    float beta = weights.y;
    float gamma = weights.z;

    //Applying Old Z (W) to correct perspective
    float rep_aw = 1/pA.w;
    float rep_bw = 1/pB.w;
    float rep_cw = 1/pC.w;

    // Perform the interpolation of all U/w and V/w values using barycentric weights and a factor of 1/w
    float u = (uvA.u*alpha*rep_aw)+(uvB.u*beta*rep_bw)+(uvC.u*gamma*rep_cw);
    
    float v = (uvA.v*alpha*rep_aw)+(uvB.v*beta*rep_bw)+(uvC.v*gamma*rep_cw);

    // Also interpolate the value of 1/w for the current pixel
    float w_reciprocal = (rep_aw*alpha) + (rep_bw*beta) + (rep_cw*gamma);

    u/= w_reciprocal;
    v/= w_reciprocal;

    uint32_t* texture = image->data;
    uint texture_width = image->width;
    uint texture_height = image->height;

    int texX = abs((int)(u*texture_width)) % texture_width;
    int texY = abs((int)(v*texture_height)) % texture_height;

    //Make the closer values have smaller values
    w_reciprocal = 1.0f - w_reciprocal;

    //Only draw the pixel if the depth value is less than the previously stored
    if(w_reciprocal < pxBuffer.z_buffer[y*pxBuffer.width+x])
    {
        pxDrawPixel(x, y, texture[(texY * texture_width) + texX]);
        //Saves into the z_buffer w_recriprocal
        pxBuffer.z_buffer[y*pxBuffer.width + x] = w_reciprocal;
    }
}


void pxTextureTriangle(
int x0, int y0, float z0, float w0, tex2D uvA,
int x1, int y1, float z1, float w1, tex2D uvB,
int x2, int y2, float z2, float w2, tex2D uvC,
uint32_t color, Image* texture)
{
    //Sort ascendingly by Y
    if(y0 > y1)
    {
        swap(y1, y0);
        swap(x1, x0);
        swap(z1, z0);
        swap(w1, w0);
        swap(uvB, uvA);
    }
    if(y1 > y2)
    {
        swap(y2, y1);
        swap(x2, x1);
        swap(z2, z1);
        swap(w2, w1);
        swap(uvC, uvB);
    }
    if(y0 > y1)
    {
        swap(y0, y1);
        swap(x0, x1);
        swap(z0, z1);
        swap(w0, w1);
        swap(uvA, uvB);
    }

    //Prepare points with 1/w for perspective correction
    vec4 pA = {x0, y0, z0, w0};
    vec4 pB = {x1, y1, z1, w1};
    vec4 pC = {x2, y2, z2, w2};

    //Render flat bottom (upper triangle)
    /////////////////////////////////////

    float inv_slope1 = 0, inv_slope2 = 0;

    int dy1 = abs(y1-y0), dy2 = abs(y2-y0);

    if(dy1)
        inv_slope1 = (float)(x1-x0)/dy1;
    if(dy2)
        inv_slope2 = (float)(x2-x0)/dy2;

    int x_start,x_end;

    if(y0-y1 != 0)
    {
        for(int y = y0; y <= y1; y++)
        {
            x_start = x1 + (y - y1)*inv_slope1;
            x_end =   x0 + (y - y0)*inv_slope2;

            if(x_start > x_end)
                swap(x_start, x_end);

            while(x_start < x_end)
            {
                pxDrawTexel(x_start, y, texture, pA, uvA, pB, uvB, pC, uvC);
                x_start++;
            }
        }
    }

    dy1 = abs(y2-y1);
    dy2 = abs(y2-y0);

    if(dy1)
        inv_slope1 = (float)(x2-x1)/dy1;
    if(dy2)
        inv_slope2 = (float)(x2-x0)/dy2;

    if(y1-y2 != 0)
    {
        for(int y = y1; y <= y2; y++)
        {
            x_start = x1 + (y-y1)*inv_slope1;
            x_end = x2 + (y-y2)*inv_slope2;
            if(x_start > x_end)
                swap(x_start, x_end);

            while(x_start < x_end)
            {
                pxDrawTexel(x_start, y, texture, pA, uvA, pB, uvB, pC, uvC);
                x_start++;
            }
        }
    }

    //Render flat top (lower triangle)
    //////////////////////////////////


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
    SDL_RenderPresent(renderer);
}

void pxDestroy(void)
{
    free(pxBuffer.data);
    free(pxBuffer.z_buffer);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}
