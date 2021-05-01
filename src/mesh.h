#ifndef MESH_H
#define MESH_H
#include "math/vector.h"
#include "triangle.h"
#include "rendering/texture.h"
#include "def.h"

typedef struct mesh_t 
{
    vec3* vertices; //Dynamic array of vertices
    tex2D* uvs;
    Image* texture; //Mesh png texture pointer
    face_t* faces; //Dynamic array of faces
    vec3 rotation; //Rotation with x, y
    vec3 scale;
    vec3 translation;
} mesh_t;

///Gets a reference
mesh_t* New_Mesh();
///Gets an array
mesh_t* Mesh_GetAllMeshes();
///Reference
mesh_t* Mesh_LoadMesh(char* obj_filename, char* png_filename, vec3 position, vec3 scale, vec3 rotation);
mesh_t Mesh_LoadObj(char* filename);
void face_debug(face_t f);
void Mesh_dispose();


#endif