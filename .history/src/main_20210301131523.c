#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "vector.h"

vec3 camera = {0, 0, 2};
bool isRunning = false;

float fov_factor = 128;
float currentAngle = 0;
int previousFrameDuration = 0;


void setup(void)
{
    pxStart();
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
        .x = fov_factor*point.x/point.z,
        .y = fov_factor*point.y/point.z
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
    int delay = FRAME_MS - (SDL_GetTicks() - previousFrameDuration);
    if(delay > 0)
    {
        SDL_Delay(delay);
        printf("%d\n",delay);
    }
    previousFrameDuration = SDL_GetTicks();
    for(int i = 0; i < NUMBER_POINTS; i++)
    {
        vec3 point = cubePoints[i];
        point = vec3_rotateY(point, currentAngle);
        point = vec3_rotateX(point, currentAngle);
        point = vec3_rotateZ(point, currentAngle);
        point = vec3_scale(point, 0.3);

        point.z-= camera.z;
        projectedPoints[i] = project(point);

    }
    currentAngle+=0.04;
}
void render(void)
{
    pxClear(0);
    // pxDrawGrid(0xFFFFFFFF, 50, 50);

    for(int i = 0; i <NUMBER_POINTS;i++)
    {
        vec2 p = projectedPoints[i];

        pxFillRect(pxBuffer.halfW+p.x, pxBuffer.halfH+p.y, 5, 5, 0xFF00FF00);
    }
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
        // camera.z+= 0.01;
    }
    cleanup();
    return 0;
}