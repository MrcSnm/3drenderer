#include "clipping.h"
#include "../triangle.h"
#include <math.h>

plane_t frustum_planes[FRUSTUM_PLANE_MAX];

void initialize_frustum(float fov_x, float fov_y, float znear, float zfar)
{
    frustum_planes[LEFT_FRUSTUM_PLANE].point = (vec3){0,0,0};
    frustum_planes[LEFT_FRUSTUM_PLANE].normal.x = cos(fov_x/2);
    frustum_planes[LEFT_FRUSTUM_PLANE].normal.y = 0;
    frustum_planes[LEFT_FRUSTUM_PLANE].normal.z = sin(fov_x/2);
    

    frustum_planes[RIGHT_FRUSTUM_PLANE].point = (vec3){0,0,0};
    frustum_planes[RIGHT_FRUSTUM_PLANE].normal.x = -cos(fov_x/2);
    frustum_planes[RIGHT_FRUSTUM_PLANE].normal.y = 0;
    frustum_planes[RIGHT_FRUSTUM_PLANE].normal.z = sin(fov_x/2);

    frustum_planes[TOP_FRUSTUM_PLANE].point = (vec3){0,0,0};
    frustum_planes[TOP_FRUSTUM_PLANE].normal.x = 0;
    frustum_planes[TOP_FRUSTUM_PLANE].normal.y = -cos(fov_y/2);
    frustum_planes[TOP_FRUSTUM_PLANE].normal.z = sin(fov_y/2);
    

    frustum_planes[BOTTOM_FRUSTUM_PLANE].point = (vec3){0,0,0};
    frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.x = 0;
    frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.y = cos(fov_y/2);
    frustum_planes[BOTTOM_FRUSTUM_PLANE].normal.z = sin(fov_y/2);

    frustum_planes[NEAR_FRUSTUM_PLANE].point = (vec3){0,0,znear};
    frustum_planes[NEAR_FRUSTUM_PLANE].normal.x = 0;
    frustum_planes[NEAR_FRUSTUM_PLANE].normal.y = 0;
    frustum_planes[NEAR_FRUSTUM_PLANE].normal.z = 1;

    frustum_planes[FAR_FRUSTUM_PLANE].point = (vec3){0,0,zfar}; 
    frustum_planes[FAR_FRUSTUM_PLANE].normal.x = 0;
    frustum_planes[FAR_FRUSTUM_PLANE].normal.y = 0;
    frustum_planes[FAR_FRUSTUM_PLANE].normal.z = -1;
}

polygon_t create_polygon_triangle(vec3 v0, vec3 v1, vec3 v2,
tex2D uv0, tex2D uv1, tex2D uv2)
{
    return (polygon_t){
        .vertices = {v0, v1, v2},
        .numVertices = 3, 
        .texcoords = {uv0, uv1, uv2}
    };
}

polygon_t create_polygon_from_triangle(triangle_t* triangle)
{
    polygon_t ret;
    for(int i = 0; i < 3; i++)
        ret.vertices[i] = vec3_from_vec4(triangle->points[i]);
    ret.numVertices = 3;
    return ret;
}
void create_triangles_from_polygon(polygon_t* polygon, triangle_t triangle_list[], out(int) num_triangles)
{
    int index0, index1, index2;
    for(int i = 0; i < polygon->numVertices - 2; i++)
    {
        index0 = 0;
        index1 = i+1;
        index2 = i+2;

        triangle_list[i].points[0] =vec4_from_vec3(polygon->vertices[index0]);
        triangle_list[i].points[1] =vec4_from_vec3(polygon->vertices[index1]);
        triangle_list[i].points[2] =vec4_from_vec3(polygon->vertices[index2]);
        triangle_list[i].texCoords[0] = polygon->texcoords[index0];
        triangle_list[i].texCoords[1] = polygon->texcoords[index1];
        triangle_list[i].texCoords[2] = polygon->texcoords[index2];
    }
    *num_triangles = polygon->numVertices-2;
}

void clip_polygon_against_plane(polygon_t* polygon, int plane)
{
    vec3 point = frustum_planes[plane].point;
    vec3 normal = frustum_planes[plane].normal;

    vec3 inside_vertices[MAX_VERTICES_PER_POLYGON];
    tex2D inside_texcoords[MAX_VERTICES_PER_POLYGON];
    int num_vertices = 0;

    vec3* current_vertex = &polygon->vertices[0];
    tex2D* current_texcoord = &polygon->texcoords[0];

    vec3* previous_vertex = &polygon->vertices[polygon->numVertices-1]; //Last 
    tex2D* previous_texcoord = &polygon->texcoords[polygon->numVertices-1]; //Last 

    float current_dot;
    float previous_dot = vec3_dot(vec3_sub(*previous_vertex, point), normal);


    while(current_vertex != &polygon->vertices[polygon->numVertices])
    {
        current_dot = vec3_dot(vec3_sub(*current_vertex, point), normal);

        //If we changed from inside to outside, calculate the intersection point
        if(current_dot * previous_dot < 0) //If they changed, the multiplication is always negative
        {
            //Find the interpolation factor
            float t = previous_dot/(previous_dot - current_dot);
            vec3 intersection_point = vec3_lerp(*previous_vertex, *current_vertex, t); //I = Q1 + t(Q2-Q1)
            tex2D intersection_uv = 
            {
                .u = previous_texcoord->u + t*(current_texcoord->u - previous_texcoord->u),
                .v = previous_texcoord->v + t*(current_texcoord->v - previous_texcoord->v),
            };
            inside_vertices[num_vertices] = intersection_point;
            inside_texcoords[num_vertices] = intersection_uv;
            num_vertices++;
        }

        //If current vertex is inside the plane (cos > 0)
        if(current_dot > 0)
        {
            inside_vertices[num_vertices] = *current_vertex;
            inside_texcoords[num_vertices] = *current_texcoord;
            num_vertices++;
        }

        //Move to the next vertex
        previous_dot = current_dot;
        previous_vertex = current_vertex;
        previous_texcoord = current_texcoord;
        current_vertex++;
        current_texcoord++;
    }

    for(int i = 0; i < num_vertices; i++)
    {
        polygon->vertices[i] = inside_vertices[i];
        polygon->texcoords[i] = inside_texcoords[i];
    }
    polygon->numVertices = num_vertices;

}

void clip_polygon(polygon_t* polygon)
{
    clip_polygon_against_plane(polygon, LEFT_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, RIGHT_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, NEAR_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, FAR_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, BOTTOM_FRUSTUM_PLANE);
    clip_polygon_against_plane(polygon, TOP_FRUSTUM_PLANE);
}