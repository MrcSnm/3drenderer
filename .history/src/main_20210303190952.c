#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"


triangle_t* triangles_to_render = null;
vec3 camera = {0, 0, -5};
bool isRunning = false;

float fov_factor = 0.5;
int previousFrameDuration = 0;


void setup(void)
{
    pxStart();
    // load_cube_mesh_data();
    mesh = Mesh_LoadObj("C:\\Users\\Hipreme\\Documents\\3dRenderer\\C\\assets\\cottage\\cottage_obj.obj");
}

void free_resources(void)
{
    Array_destroy(mesh.vertices);
    Array_destroy(mesh.faces);
}

void destroy_window(void)
{
    pxDestroy();
    SDL_Quit();
}

void cleanup(void)
{
    free_resources();
    destroy_window();
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
    triangles_to_render = Array(triangle_t, 16);

    int n_faces = Array_length(mesh.faces);
    // mesh.rotation.x+=0.01;
    // mesh.rotation.y+=0.01;
    // mesh.rotation.z+=0.01;
    for(int i = 0; i < n_faces; i++)
    {
        face_t currentFace = mesh.faces[i];
        triangle[0] = mesh.vertices[currentFace.a];
        triangle[1] = mesh.vertices[currentFace.b];
        triangle[2] = mesh.vertices[currentFace.c];

        triangle_t projectedTriangle;
        for(int j = 0; j < 3; j++)
        {
            vec3 transformed_vertex = triangle[j];
            //Apply transformation for each vertex
            transformed_vertex = vec3_rotateX(transformed_vertex, mesh.rotation.x);
            transformed_vertex = vec3_rotateY(transformed_vertex, mesh.rotation.y);
            transformed_vertex = vec3_rotateZ(transformed_vertex, mesh.rotation.z);
            //Translate the vertess away from the camera
            transformed_vertex.z-= camera.z;
            
            vec2 projection = project(transformed_vertex);
            //Scale and translate to the screen center
            projection.x+= pxBuffer.halfW;
            projection.y+= pxBuffer.halfH;  
            projectedTriangle.points[j] = projection;
        }
        //Save the projected triangle
        Array_push(triangles_to_render, projectedTriangle);
    }
    previousFrameDuration = SDL_GetTicks();
}
void render(void)
{
    pxClear(0);
    // pxDrawGrid(0xFFFFFFFF, 50, 50);
    int n_triangles = Array_length(triangles_to_render);
    for(int i = 0; i < n_triangles; i++)
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
    Array_destroy(triangles_to_render);
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