#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "vector.h"

#define NUMBER_POINTS (9*9*9)
vec3 cubePoints[NUMBER_POINTS];
vec2 projectedPoints[NUMBER_POINTS];

bool isRunning = false;


int PX = 1000;
int PY = 400;

float fov_factor = 128;

void setup(void)
{
    pxStart();

    int i = 0;
    for(float x = -1; x <= 1; x+=0.25)
        for(float y = -1; y <= 1; y+=0.25)
            for(float z = -1; z <= 1; z+=0.25)
                cubePoints[i++] = (vec3){x, y, z};
}

void cleanup(void)
{
    pxDestroy();
    SDL_Quit();
}

///Function that receives a 3D point and returns a 2D
vec2 project(vec3 point)
{
    vec2 projectedPoint = {
        .x = fov_factor*point.x,
        .y = fov_factor*point.y
    };

    return projectedPoint;
}


void process_input(void)
{
    static SDL_Event ev;
    SDL_PollEvent(&ev);

    switch (ev.type)
    {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(ev.key.keysym.sym == SDLK_ESCAPE)
                isRunning = false;
        default:
            break;
    }
}
void update(void)
{
    for(int i = 0; i < NUMBER_POINTS; i++)
    {
        vec3 point = cubePoints[i];
        projectedPoints[i] =  project(point);
    }
}
void render(void)
{
    pxClear(0);
    pxDrawGrid(0xFFFFFFFF, 50, 50);
    for(int i = 0; i <NUMBER_POINTS;i++)
    {
        vec2 p = projectedPoints[i];
        pxFillRect(pxBuffer.halfW+p.x, pxBuffer.halfH+p.y, 5, 5, 0xFF00FF00);
    }

    pxFillRect(PX, PY, 50, 50, 0xFFFF0000);
    pxRender();
    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[])
{
    isRunning = initialize_window();
    setup();

    while (isRunning)
    {
        process_input();
        update();
        render();
        SDL_Delay(16);
        PX++;
    }
    cleanup();
    return 0;
}