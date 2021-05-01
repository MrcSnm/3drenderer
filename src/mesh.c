#include "mesh.h"
#include "rendering/texture.h"
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

static mesh_t* meshes;
mesh_t* New_Mesh()
{
    if(meshes == null)
        meshes = Array(mesh_t, 8);
    mesh_t mesh = (mesh_t){
        .vertices = null,
        .texture = null,
        .faces = null,
        .translation = {0,0,0},
        .scale = {1,1,1}, 
        .rotation = {0,0,0}
    };
    Array_push(meshes, mesh);
    return &meshes[Array_length(meshes)-1];
}

enum OBJ_MODE
{
    DEFAULT,
    TEXTURE,
    NORMAL
};

mesh_t Mesh_LoadObj(char* filename)
{
    mesh_t ret ={
        .faces = null,
        .uvs = null,
        .vertices = null,
        .rotation = {0,0,0},
        .scale = {1,1,1},
        .translation = {0,0,0}
    };
    tex2D tempTex;
    char* content = File_readText(filename);
    if(!content)
        return ret;
    int length = strlen(content);

    ret.vertices = Array(vec3, 64);
    ret.uvs = Array(tex2D, 64);
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
                        ((float*)&v)[index] = atof(number);
                        if(index == 2)
                        {
                            fprintf(stderr, "Invavlid obj file, exiting with -1");
                            exit(-1);
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
                ((float*)&v)[index] = atof(number);
                memset(number, 0, 16);
                numIndex = 0;
                switch (mode)
                {
                case DEFAULT:
                    Array_push(ret.vertices, v);
                    break;
                case TEXTURE:
                    tempTex = (tex2D){.u = v.x, .v = 1-v.y};
                    Array_push(ret.uvs, tempTex);
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

                face_t faces[3]; //v, vt, vn
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
                    c = content[i];
                }
                face_t* currentFace =  &(faces[indexFace]);
                *((int*)currentFace+index) = atoi(number);
                currentFace->color = 0xFFFFFFFF;
                memset(number, 0, 16);
                //Now handle the texture coordinates
                
                faces[0].a_uv = ret.uvs[faces[1].a-1];
                faces[0].b_uv = ret.uvs[faces[1].b-1];
                faces[0].c_uv = ret.uvs[faces[1].c-1];

                if(faces[1].d != -1)
                    faces[0].d_uv = ret.uvs[faces[1].d-1];
                Array_push(ret.faces, faces[0]); //Push common vertex face

                if(faces[0].d != -1)
                {
                    // printf("%d\n", faces[0].d);
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

mesh_t* Mesh_LoadMesh(char* obj_filename, char* png_filename, vec3 position, vec3 scale, vec3 rotation)
{
    mesh_t* ret = New_Mesh();
    *ret = Mesh_LoadObj(obj_filename);
    ret->texture = load_image(png_filename);
    ret->translation = position;
    ret->rotation = rotation;
    return ret;
}

mesh_t* Mesh_GetAllMeshes()
{
    if(meshes == null)
        meshes = Array(mesh_t, 8);
    return meshes;
}


void Mesh_dispose()
{
    for(int i = 0; i < Array_length(meshes); i++)
    {
        Array_destroy(meshes[i].vertices);
        Array_destroy(meshes[i].uvs);
    }
    Array_destroy(meshes);
}