#include "mesh.h"
#include "array.h"
#include "file.h"

mesh_t mesh =
{
    null,
    null,
    {0,0,0}
};

vec3 cube_vertices[N_CUBE_VERTICES] = {
    { .x = -1, .y = -1, .z = -1 }, // 1
    { .x = -1, .y =  1, .z = -1 }, // 2
    { .x =  1, .y =  1, .z = -1 }, // 3
    { .x =  1, .y = -1, .z = -1 }, // 4
    { .x =  1, .y =  1, .z =  1 }, // 5
    { .x =  1, .y = -1, .z =  1 }, // 6
    { .x = -1, .y =  1, .z =  1 }, // 7
    { .x = -1, .y = -1, .z =  1 }  // 8
};
face_t cube_faces[N_CUBE_FACES] = {
    //Front
    {0, 1, 2},
    {0, 2, 3},
    //Right
    {3, 2, 4},
    {3, 4, 5},
    //Back
    {5, 4, 6},
    {5, 6, 7},
    //Left
    {7, 6, 1},
    {7, 1, 0},
    //Top
    {1, 6, 4},
    {1, 4, 2},
    //Bottom,
    {5, 7, 0},
    {5, 0, 3}
};

void load_cube_mesh_data(void)
{
    mesh.vertices = Array(vec3, N_CUBE_VERTICES);
    for(int i = 0; i < N_CUBE_VERTICES; i++)
        Array_push(mesh.vertices, cube_vertices[i]);
    mesh.faces = Array(face_t, N_CUBE_FACES);
    for(int i = 0; i < N_CUBE_FACES; i++)
        Array_push(mesh.faces, cube_faces[i]);
}

static enum OBJ_MODE 
{
    DEFAULT,
    NORMAL,
    TEXTURE
};

mesh_t Mesh_LoadObj(char* filename)
{
    mesh_t ret;
    char* content = File_readText(filename);
    int length = strlen(content);
    if(!length)
        return ret;

    ret.vertices = Array(vec3, 64);
    ret.faces = Array(face_t, 64);
    ret.rotation = (vec3){0,0,0};

    bool ignore = false;
    char c;
    int lineCounter = 0;
    char number[128];
    memset(number, 0, 128);

    int mode = DEFAULT;
    for(int i = 0; i < length; i++)
    {
        c = content[i];
        if(c == '#')
            ignore = true;
        if(c == '\n')
        {
            ignore = false;
            lineCounter=0;
        }
        if(ignore)
            continue;
        if(lineCounter == 0)
        {
            if(c == 'v')//Vertice
            {
                i++;
                lineCounter++;
                char c = content[i];
                if(c == 't')
                {
                    mode = TEXTURE;
                    i++;
                    lineCounter++;
                }
                else if(c == 'n')
                {
                    mode = NORMAL;
                    i++;
                    lineCounter++;
                }
                else
                    mode = DEFAULT;


            }
        }
        lineCounter++;
    }
}