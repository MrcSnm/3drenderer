#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"


triangle_t* triangles_to_render;
vec3 camera = {0, 0, -5};
bool isRunning = false;

float fov_factor = 256;
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
        SDL_Delay(delay);
    vec3 triangle[3];

    for(int i = 0; i < N_CUBE_FACES; i++)
    {
        face_t currentFace = cube_faces[i];
        triangle[0] = mesh_vertices[currentFace.a];
        triangle[1] = mesh_vertices[currentFace.b];
        triangle[2] = mesh_vertices[currentFace.c];

        triangle_t projectedTriangle;
        for(int j = 0; j < 3; j++)
        {
            vec3 transformed_vertex = triangle[j];
            //Apply transformation for each vertex
            transformed_vertex = vec3_rotateX(transformed_vertex, currentAngle);
            transformed_vertex = vec3_rotateY(transformed_vertex, currentAngle);
            transformed_vertex = vec3_rotateZ(transformed_vertex, currentAngle);
            //Translate the vertess away from the camera
            transformed_vertex.z-= camera.z;
            
            vec2 projection = project(transformed_vertex);
            //Scale and translate to the screen center
            projection.x+= pxBuffer.halfW;
            projection.y+= pxBuffer.halfH;  
            projectedTriangle.points[j] = projection;
        }
        //Save the projected triangle
        triangles_to_render[i] = projectedTriangle;
    }
    previousFrameDuration = SDL_GetTicks();
  
    currentAngle+=0.04;
}
void render(void)
{
    pxClear(0);
    // pxDrawGrid(0xFFFFFFFF, 50, 50);
    for(int i = 0; i < N_CUBE_FACES; i++)
    {
        triangle_t t = triangles_to_render[i];

        pxDrawTriangle(
            t.points[0].x, t.points[0].y,
            t.points[1].x, t.points[1].y,
            t.points[2].x, t.points[2].y,
            0xFFFF0000
        );
    }


    pxRender();
    SDL_RenderPresent(renderer);
}


int main(int argc, char* argv[])
{
    isRunning = initialize_window();
    int* b = Array(int, 10);

    printf("%d\n", Array_capacity(b));
    for(int i = 0; i < Array_capacity(b); i++)
        Array_push(b, i);

    Array_push(b, 55);
    printf("%d", b[-2]);

    for(int i = 0; i < Array_length(b); i++)
        printf("%d\n", b[i]);

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