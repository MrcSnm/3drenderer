#ifndef MESH_H
#define MESH_H
#include "vector.h"
#include "triangle.h"

#define N_MESH_VERTICES 8

extern vec3 mesh_vertices[N_MESH_VERTICES];

#define N_CUBE_FACES 6*2

//6 faces, 2 triangles per face
extern face_t cube_faces[N_CUBE_FACES];
#endif