#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "vector.h"

#define NUMBER_POINTS (9*9*9)
vec3 cubePoints[NUMBER_POINTS];


bool isRunning = false;


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

}
void render(void)
{
    pxClear(0);
    pxDrawGrid(0xFFFFFFFF, 50, 50);
    pxFillRect(50, 0, 50, 50, 0xFFFFFF00);

    int hw = pxBuffer.width/2;
    int hh = pxBuffer.height/2;
    for(int i = 0;i < NUMBER_POINTS; i++)
    {
        vec3 v = cubePoints[i];
        int x = hw+(hw*v.x);
        int y = hh+(hh*v.y);

        // printf("%d, %d\n", x, y);

        pxFillRect(x, y, 20, 20, 0xFFFFFF00);
    }

    // printf("%d, %d", pxBuffer.width, pxBuffer.height);

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
    }
    cleanup();
    return 0;
}