#include "mesh.h"

vec3 mesh_vertices[N_MESH_VERTICES] = {
    {-1, -1, -1},
    {-1,  1, -1},
    { 1,  1, -1},
    { 1, -1, -1},
    { 1,  1,  1},
    { 1, -1,  1},
    {-1,  1,  1},
    {-1, -1,  1}
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