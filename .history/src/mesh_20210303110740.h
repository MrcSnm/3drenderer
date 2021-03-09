#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "triangle.h"
#include "def.h"

#define N_CUBE_VERTICES 8
#define N_CUBE_FACES 6*2

extern vec3 cube_vertices[N_CUBE_VERTICES];
extern face_t cube_faces[N_CUBE_FACES];//6 faces, 2 triangles per face

typedef struct mesh_t 
{
    vec3* vertices; //Dynamic array of vertices
    face_t* faces; //Dynamic array of faces
    vec3 rotation; //Rotation with x, y
} mesh_t;

extern mesh_t mesh;


void load_cube_mesh_data(void);

mesh_t Mesh_LoadObj(char* filename);


#endif