#ifndef TEXTURE_H
#define TEXTURE_H
#include <stdint.h>
#include "../loading/upng.h"


typedef struct tex2D
{
    float u,v;
} tex2D;

typedef struct Image
{
    unsigned int width, height;
    uint32_t* data;
} Image;

extern const uint8_t REDBRICK_TEXTURE[];
extern uint32_t* mesh_texture;
extern int texture_width;
extern int texture_height;


//Texture loading section
Image load_image(char* path);
void free_images();

#endif