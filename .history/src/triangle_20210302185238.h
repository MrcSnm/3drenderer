#ifndef TRIANGLE_H
#define TRIANGLE_H

typedef struct face_t
{
    int a,b,c;
} face_t;

typedef struct triangle_t
{
    vec2 points[3]
} triangle_t;

#endif