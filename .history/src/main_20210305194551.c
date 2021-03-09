#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "vector.h"
#include "mesh.h"
#include "array.h"
#include "input.h"


triangle_t* triangles_to_render = null;
vec3 camera = {0, 0, -5};
bool isRunning = false;

float fov_factor = 512;
int previousFrameDuration = 0;

/////////////////////////////////////////////////////////////////////
// Input functions
/////////////////////////////////////////////////////////////////////

///Key ESC
void exit_application(void){isRunning = false;}
///Key 1
void set_wireframe_vertex(void){PXRenderer_setState(PX_STATES_LINE|PX_STATES_VERTEX);}
///Key 2
void set_wireframe_only(void){PXRenderer_setState(PX_STATES_LINE);}
///Key 3
void set_filled_only(void){PXRenderer_setState(PX_STATES_FILL);}
///Key 4
void set_filled_wireframe(void){PXRenderer_setState(PX_STATES_FILL|PX_STATES_LINE);}
///Key C
void set_culling_enabled(void){PXRenderer_setCulling(PX_CULL_FRONT);}
///Key D
void set_culling_disabled(void){PXRenderer_setCulling(PX_CULL_NONE);}

void start_input()
{
    ///Key ESC
    Input_setKeyHandler(SDLK_ESCAPE, &exit_application);
    ///Key 1
    Input_setKeyHandler('1', &set_wireframe_vertex);
    ///Key 2
    Input_setKeyHandler('2', &set_wireframe_only);
    ///Key 3
    Input_setKeyHandler('3', &set_filled_only);
    ///Key 4
    Input_setKeyHandler('4', &set_filled_wireframe);
    ///Key C
    Input_setKeyHandler('C', &set_culling_enabled);
    ///Key D
    Input_setKeyHandler('D', &set_culling_disabled);
}

void setup(void)
{
    start_input();
    pxStart();
    // load_cube_mesh_data();
    triangles_to_render = Array(triangle_t, 256);
    mesh = Mesh_LoadObj("C:\\Users\\Hipreme\\Documents\\3dRenderer\\C\\assets\\cube.obj");
    // mesh = Mesh_LoadObj("C:\\Users\\Hipreme\\Documents\\3dRenderer\\C\\assets\\f22.obj");
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

bool culling(vec3 a, vec3 b, vec3 c, vec3 camPos)
{
    vec3 b_a = vec3_sub(b, a);
    vec3 c_a = vec3_sub(c, a);
    vec3 normal = vec3_cross(b_a, c_a);
    vec3 camRay = vec3_sub(camPos, a);
    return vec3_dot(normal, camRay) < 0;
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
            Input_exec(ev.key.keysym.sym);
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

    int n_faces = Array_length(mesh.faces);
    mesh.rotation.x+=0.01;
    mesh.rotation.y+=0.01;
    mesh.rotation.z+=0.01;
    for(int i = 0; i < n_faces; i++)
    {
        face_t currentFace = mesh.faces[i];
        triangle[0] = mesh.vertices[currentFace.a];
        triangle[1] = mesh.vertices[currentFace.b];
        triangle[2] = mesh.vertices[currentFace.c];

        triangle_t projectedTriangle;
        vec3 transformed_vertex[3];
        for(int j = 0; j < 3; j++)
        {
            transformed_vertex[j] = triangle[j];
            //Apply transformation for each vertex
            if(mesh.rotation.x)
                transformed_vertex[j] = vec3_rotateX(transformed_vertex[j], mesh.rotation.x);
            if(mesh.rotation.y)
                transformed_vertex[j] = vec3_rotateY(transformed_vertex[j], mesh.rotation.y);
            if(mesh.rotation.z)
                transformed_vertex[j] = vec3_rotateZ(transformed_vertex[j], mesh.rotation.z);
            //Translate the vertess away from the camera
            transformed_vertex[j].z-= camera.z;
        }

        if(pxRenderer.cullType == PX_CULL_FRONT)
        {
            if(culling(transformed_vertex[0], transformed_vertex[1], transformed_vertex[2], camera))
                continue;
        }
        
        for(int j = 0; j < 3; j++)
        {
            vec2 projection = project(transformed_vertex[j]);
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
        int r, g, b;
        r = rand() %255;
        g = rand() %255;
        b = rand() %255;

        pxFillTriangle(
            t.points[0].x, t.points[0].y,
            t.points[1].x, t.points[1].y,
            t.points[2].x, t.points[2].y,
            0xFFFFFF00
            // 0xFF000000 + (r<<16) +(g<<8)+b
        );
        pxDrawTriangle(
            t.points[0].x, t.points[0].y,
            t.points[1].x, t.points[1].y,
            t.points[2].x, t.points[2].y,
            0xFFF00F00
            // 0xFF000000 + (r<<16) +(g<<8)+b
        );
    }

    // const int t = 300;
    // pxFillTriangle(t+100, t+100, t+200, t-100, t+300, t+100, 0xFFFF0000);
    // pxDrawTriangle(t+100, t+100, t+200, t-100, t+300, t+100, 0xFFFFFF00);
    // pxFillTriangle(t+100, t+100, t+200, t+300, t+300, t+100, 0xFFFF0000);
    // pxDrawTriangle(t+100, t+100, t+200, t+300, t+300, t+100, 0xFFFFFF00);
    pxRender();
    SDL_RenderPresent(renderer);
    Array_clear(triangles_to_render);
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