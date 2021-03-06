#include "texture.h"
#include "../def.h"
#include "../array.h"

/// DEFINES  A const uint8_t REDBRICK_TEXTURE, all copyrights goes to Wolfenstein3D
const uint8_t REDBRICK_TEXTURE[] =
#include "_red_brick_texture.h"
;
static upng_t** imagesLoaded = null;
static Image* loaded_images = null;
static size_t imagesCount = 0;

Image* load_image(char* path)
{
    if(imagesCount == 0)
    {
        imagesLoaded = NEW(upng_t*, 1);
        loaded_images = Array(Image, 1);
    }
    else
        imagesLoaded = realloc(imagesLoaded, sizeof(upng_t*)*imagesCount+1);
    Image ret = {.data = null, .width = 0,  .height = 0};
    upng_t* file = upng_new_from_file(path);
    if(file != null)
    {
        upng_decode(file);
        if(upng_get_error(file) == UPNG_EOK)
        {
            ret.data = (uint32_t*)upng_get_buffer(file);
            ret.width = upng_get_width(file);
            ret.height = upng_get_height(file);
            Array_push(loaded_images, ret);
            imagesLoaded[imagesCount++] = file;
            return &loaded_images[Array_length(loaded_images)-1];
        }
    }
    return null;
}

void free_images(void)
{
    for(int i = 0; i < imagesCount; i++)
        upng_free(imagesLoaded[i]);
}