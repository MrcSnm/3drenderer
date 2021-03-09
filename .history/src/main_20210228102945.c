#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "vector.h"

static const int NUMBER_POINTS = 9*9*9;
vec3 cubePoints[9*9*9];


bool isRunning = false;


void setup(void)
{
    pxStart();
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