#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "def.h"
#include "renderer.h"
#include "math/vector.h"
#include "math/matrix.h"
#include "mesh.h"
#include "array.h"
#include "input.h"
#include <time.h>
#include "algorithms/sort.h"


triangle_t* triangles_to_render = null;
vec3 camera = {0, 0, -5};
bool isRunning = false;

int previousFrameDuration = 0;
float fov_angle = M_PI/3; //30 degrees
float zfar = 100;
float znear = 0.1;
mat4 proj_matrix;

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
void set_culling_enabled(void){PXRenderer_setCulling(PX_CULL_BACK);}
///Key D
void set_culling_disabled(void){PXRenderer_setCulling(PX_CULL_NONE);}

void start_input()
{
    Input_setKeyHandler(SDLK_ESCAPE, &exit_application);
    Input_setKeyHandler('1', &set_wireframe_vertex);
    Input_setKeyHandler('2', &set_wireframe_only);
    Input_setKeyHandler('3', &set_filled_only);
    Input_setKeyHandler('4', &set_filled_wireframe);
    Input_setKeyHandler('C', &set_culling_enabled);
    Input_setKeyHandler('D', &set_culling_disabled);
}

void setup(void)
{
    start_input();
    pxStart();
    load_cube_mesh_data();
    triangles_to_render = Array(triangle_t, 256);
    proj_matrix = mat4_perspective_mat( pxBuffer.height/(float)pxBuffer.width, fov_angle, znear, zfar);
    // mesh = Mesh_LoadObj("C:\\Users\\Hipreme\\Documents\\3dRenderer\\C\\assets\\cube.obj");
    // mesh = Mesh_LoadObj("C:\\Users\\Hipreme\\Documents\\3dRenderer\\C\\assets\\f22.obj");
}

void free_resources(void);
void destroy_window(void);
void cleanup(void);

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
        case SDL_MOUSEWHEEL:
            if(Input_hasWheelMoved(&ev.wheel))
            {
                if(Input_hasWheelMovedDown(&ev.wheel))
                    fov_angle-= DEGREES(1);
                else
                    fov_angle+= DEGREES(1);
                proj_matrix = mat4_perspective_mat(pxBuffer.height/(float)pxBuffer.width, fov_angle, znear, zfar);
            }
        default:
            break;
    }
}

int triangles_sort_asc(void* a, void *b)
{
    float fa = ((triangle_t*)a)->avg_depth;
    float fb = ((triangle_t*)b)->avg_depth;
    return (fa > fb) - (fa < fb);

}

void update(void)
{
    int delay = FRAME_MS - (SDL_GetTicks() - previousFrameDuration);
    if(delay > 0)
        SDL_Delay(delay);
    vec3 triangle[3];

    int n_faces = Array_length(mesh.faces);
    mesh.rotation.x+=0.01;
    // mesh.rotation.y+=0.01;
    // mesh.rotation.z+=0.01;

    // mesh.translation.x+= 0.01;
    //Translate the vertexes away from the camera
    mesh.translation.z = -camera.z;

    //Create a scale matrix
    mat4 sm = mat4_scale_mat(mesh.scale.x, mesh.scale.y, mesh.scale.z);
    mat4 tm = mat4_translation_mat(mesh.translation.x, mesh.translation.y, mesh.translation.z);
    mat4 rmX = mat4_rotationX_mat(mesh.rotation.x);
    mat4 rmY = mat4_rotationY_mat(mesh.rotation.y);
    mat4 rmZ = mat4_rotationZ_mat(mesh.rotation.z);

    // mat4 world_mat = mat4_mult_mat4(mat4_mult_mat4(mat4_mult_mat4(sm, rmX), rmY), rmZ);
    mat4 world_mat = sm;
    world_mat = mat4_mult_mat4(rmX, world_mat);
    world_mat = mat4_mult_mat4(rmY, world_mat);
    world_mat = mat4_mult_mat4(rmZ, world_mat);
    world_mat = mat4_mult_mat4(tm, world_mat);
    
    for(int i = 0; i < n_faces; i++)
    {
        face_t currentFace = mesh.faces[i];
        triangle[0] = mesh.vertices[currentFace.a];
        triangle[1] = mesh.vertices[currentFace.b];
        triangle[2] = mesh.vertices[currentFace.c];

        vec4 transformed_vertex[3];
        for(int j = 0; j < 3; j++)
        {
            transformed_vertex[j] = vec4_from_vec3(triangle[j]);
            //Apply transformation for each vertex
            transformed_vertex[j] = mat4_mult_vec4(world_mat, transformed_vertex[j]);
        }

        if(pxRenderer.cullType == PX_CULL_BACK)
        {
            if(culling(
                vec3_from_vec4(transformed_vertex[0]),
                vec3_from_vec4(transformed_vertex[1]),
                vec3_from_vec4(transformed_vertex[2]),
             camera))
                continue;
        }

        vec3 vA = vec3_from_vec4(transformed_vertex[0]);
        vec3 vB = vec3_from_vec4(transformed_vertex[1]);
        vec3 vC = vec3_from_vec4(transformed_vertex[2]);

        //B - A = dirB
        //C - A = dirC
        //Normal = dir
        vec3 normal = vec3_cross(vec3_sub(vB, vA), vec3_sub(vC, vA));
        vec3_normallize(&normal);
        float color = vec3_dot((vec3){1.0, 0.0, 0.0}, normal);
        printf("%f\n", color);
        
        vec4 projection[3];
        for(int j = 0; j < 3; j++)
        {
            projection[j] = mat4_project(proj_matrix, transformed_vertex[j]);
            // //Scale to the viewport
            projection[j].x *= pxBuffer.halfW;
            projection[j].y *= pxBuffer.halfH;

            //Translate to the screen center
            projection[j].x+= pxBuffer.halfW;
            projection[j].y+= pxBuffer.halfH;

        }
        triangle_t projectedTriangle = {
            .points = 
            {
                {projection[0].x, projection[0].y},
                {projection[1].x, projection[1].y},
                {projection[2].x, projection[2].y}
            },
            .color = currentFace.color*color,
            .avg_depth = (transformed_vertex[0].z+transformed_vertex[1].z+
            transformed_vertex[2].z)/ 3.0f
        };
        //Save the projected triangle
        Array_push(triangles_to_render, projectedTriangle);
        insert_sort(triangles_to_render, Array_length(triangles_to_render), &triangles_sort_asc);
    }
    previousFrameDuration = SDL_GetTicks();

    //Sort the triangles
}
void render(void)
{
    pxClear(0);
    // pxDrawGrid(0xFFFFFFFF, 50, 50);
    int n_triangles = Array_length(triangles_to_render);
    for(int i = 0; i < n_triangles; i++)
    {
        triangle_t t = triangles_to_render[i];
        // int r, g, b;
        // r = rand() %255;
        // g = rand() %255;
        // b = rand() %255;

        if(PXRenderer_has(PX_STATES_FILL))
            pxFillTriangle(
                t.points[0].x, t.points[0].y,
                t.points[1].x, t.points[1].y,
                t.points[2].x, t.points[2].y,
                t.color
                // 0xFF000000 + (r<<16) +(g<<8)+b
            );
        if(PXRenderer_has(PX_STATES_LINE))
            pxDrawTriangle(
                t.points[0].x, t.points[0].y,
                t.points[1].x, t.points[1].y,
                t.points[2].x, t.points[2].y,
                0xFFFFFFFF
                // 0xFF000000 + (r<<16) +(g<<8)+b
            );
        if(PXRenderer_has(PX_STATES_VERTEX))
        {
            pxFillRect(t.points[0].x, t.points[0].y, 4, 4, 0xFF0000);
            pxFillRect(t.points[1].x, t.points[1].y, 4, 4, 0xFF0000);
            pxFillRect(t.points[2].x, t.points[2].y, 4, 4, 0xFF0000);

        }
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