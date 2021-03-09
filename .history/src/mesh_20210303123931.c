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
    TEXTURE,
    NORMAL
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
    char number[16];
    int numIndex = 0;

    memset(number, 0, 16);

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
                c = content[i];
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
                i++; //Advance from space(\s)
                lineCounter++;
                c = content[i];
                int index = 0;
                vec3 v;
                while(c != '\n')
                {
                    if(c == ' ')//Advance to x, y...
                    {
                        switch (index)
                        {
                        case 0:
                            v.x = atof(number);
                            break;
                        case 1:
                            v.y = atof(number);
                            break;
                        default:
                            exit(-1);
                            break;
                        }
                        memset(number, 0, 16);
                        index++;
                        numIndex = 0;
                    }
                    else
                        number[numIndex] = c;
                    numIndex++;
                    i++;
                    lineCounter++;
                    c = content[i];
                }
                v.z = atof(number);
                memset(number, 0, 16);
                numIndex = 0;
                switch (mode)
                {
                case DEFAULT:
                    Array_push(ret.vertices, v);
                    break;
                default:
                    break;
                }
            }
            else if(c == 'f')
            {
                i+=2;
                c = content[i];
                face_t faces[4]; //Some has 4
                int index = 0;
                int indexFace = 0;
                while(c != '\n')
                {
                    if(c == '/')
                    {
                        face_t* currentFace =  &faces[indexFace];
                        *((int*)currentFace+index) = atoi(number);
                        memset(number, 0, 16);
                        indexFace++;
                    }
                    else if(c == ' ')
                    {
                        face_t* currentFace =  &faces[indexFace];
                        *((int*)currentFace+index) = atoi(number);
                        memset(number, 0, 16);
                        index++;
                        indexFace = 0;
                    }
                    else
                        number[numIndex] = c;
                    i++;
                    lineCounter++;
                    numIndex++;
                    c = content[i];
                }
            }
        }
        lineCounter++;
    }
}