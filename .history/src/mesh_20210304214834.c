#include "mesh.h"
#include "array.h"
#include "file.h"
#include "utils.h"
#include <stdio.h>

void face_debug(face_t f)
{
    debug_start
        printf("Face debug info:\n\tA: %d, B: %d, C: %d, D: %d\n",
            f.a, f.b, f.c, f.d
        );
    debug_end
}

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
    {0, 1, 2,-1},
    {0, 2, 3,-1},
    //Right
    {3, 2, 4,-1},
    {3, 4, 5,-1},
    //Back
    {5, 4, 6,-1},
    {5, 6, 7,-1},
    //Left
    {7, 6, 1,-1},
    {7, 1, 0,-1},
    //Top
    {1, 6, 4,-1},
    {1, 4, 2,-1},
    //Bottom,
    {5, 7, 0,-1},
    {5, 0, 3,-1}
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
    if(!content)
        return ret;
    int length = strlen(content);

    ret.vertices = Array(vec3, 64);
    ret.faces = Array(face_t, 64);

    ret.rotation = (vec3){0,0,0};

    bool ignore = false;
    char c;
    bool newLine = true;
    char number[16];
    int numIndex = 0;

    memset(number, 0, 16);

    int mode = DEFAULT;
    for(size_t i = 0; i < length; i++)
    {
        c = content[i];
        if(c == '#')
            ignore = true;
        if(c == '\n')
        {
            ignore = false;
            newLine = true;
            continue;
        }
        if(ignore)
            continue;
        if(newLine)
        {
            if(c == 'v')//Vertice
            {
                i++;
                c = content[i];
                if(c == 't')
                {
                    mode = TEXTURE;
                    i++;
                }
                else if(c == 'n')
                {
                    mode = NORMAL;
                    i++;
                }
                else
                    mode = DEFAULT;
                do{   
                    c = content[++i];//Advance from space(\s)
                }while(c == ' ');
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
                            fprintf(stderr, "Invavlid obj file, exiting with -1");
                            exit(-1);
                            break;
                        }
                        memset(number, 0, 16);
                        index++;
                        numIndex = 0;
                    }
                    else
                    {
                        number[numIndex] = c;
                        numIndex++;
                    }
                    i++;
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
                continue;
            }
            else if(c == 'f')
            {
                do{
                    c = content[++i];
                }while(c == ' ');

                face_t faces[3]; //v, vt, vs
                faces[0].d = -1;
                faces[1].d = -1;
                faces[2].d = -1;
                int index = 0;
                int indexFace = 0;
                numIndex=0;


                while(c != '\n')
                {
                    if(c == '/')
                    {
                        face_t* currentFace =  &(faces[indexFace]);
                        *((int*)currentFace+index) = atoi(number);
                        memset(number, 0, 16);
                        numIndex = 0;
                        indexFace++;
                    }
                    else if(c == ' ' && strIsNumberChar(content[i+1]))
                    {
                        face_t* currentFace =  &(faces[indexFace]);
                        *((int*)currentFace+index) = atoi(number);
                        memset(number, 0, 16);
                        numIndex = 0;
                        index++;
                        indexFace = 0;
                        if(index >= 4)
                        {
                            fprintf(stderr, "Mesh with more than 4 vertices per face is not supported\n"
                            "\tError at line '%d' on file '%s'.\n", strCountLinesUntil(content, i), filename);
                            exit(-1);
                        }
                    }
                    else if(strIsNumberChar(c))
                    {
                        number[numIndex] = c;
                        numIndex++;
                    }
                    i++;
                    if(i+1 == length)
                    {
                        printf("\n%s\n", content);
                    }
                    c = content[i];
                }
                face_t* currentFace =  &(faces[indexFace]);
                *((int*)currentFace+index+1) = atoi(number);
                memset(number, 0, 16);
                Array_push(ret.faces, faces[0]);
                if(faces[0].d != -1)
                {
                    swap(faces[0].b, faces[0].d);
                    Array_push(ret.faces, faces[0]);
                }
                continue;
            }
        }
        newLine = false;
    }
    //Now normalize faces to be -1
    for(int i = 0, len = Array_length(ret.faces); i < len; i++)
    {
        ret.faces[i].a--;
        ret.faces[i].b--;
        ret.faces[i].c--;
        ret.faces[i].d--;
    }
    return ret;
}