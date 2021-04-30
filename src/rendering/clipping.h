#ifndef CLIPPING_H
#define CLIPPING_H
#include "../def.h"
#include "../math/vector.h"
#include "../triangle.h"

#define MAX_VERTICES_PER_POLYGON 10
#define MAX_TRIANGLES_PER_POLYGON 10

enum {
    LEFT_FRUSTUM_PLANE,
    RIGHT_FRUSTUM_PLANE,
    TOP_FRUSTUM_PLANE,
    BOTTOM_FRUSTUM_PLANE,
    NEAR_FRUSTUM_PLANE,
    FAR_FRUSTUM_PLANE,
    FRUSTUM_PLANE_MAX
};

typedef struct plane_t
{
    vec3 point;
    vec3 normal;
} plane_t;

typedef struct polygon_t
{
    vec3 vertices[MAX_VERTICES_PER_POLYGON];
    tex2D texcoords[MAX_VERTICES_PER_POLYGON];
    int numVertices;
} polygon_t;


extern plane_t frustum_planes[FRUSTUM_PLANE_MAX];
void initialize_frustum(float fov_x, float fov_y, float znear, float zfar);
polygon_t create_polygon_triangle(vec3 v0, vec3 v1, vec3 v2, tex2D uv0, tex2D uv1, tex2D uv2);
polygon_t create_polygon_from_triangle(triangle_t* triangle);
void create_triangles_from_polygon(polygon_t* polygon, triangle_t triangle_list[], out(int) num_triangles);
void clip_polygon_against_plane(polygon_t* polygon, int plane);
void clip_polygon(polygon_t* polygon);

#endif  