#include "image.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

typedef struct
{
    const void* data;
    int size;
    int offset;
} png_image_source;

void func_read_png(png_structp png_ptr, png_bytep data, png_size_t len)
{
    png_image_source* isrc = (png_image_source*)png_get_io_ptr(png_ptr);
    if (isrc->offset + len <= isrc->size)
    {
        memcpy(data, isrc->data + isrc->offset, len);
        isrc->offset += len;
    }
}

void load_png(struct image_unit* img, const void* buffer, const int len)
{
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    setjmp(png_jmpbuf(png_ptr));
    png_image_source imgs;
    imgs.data = buffer;
    imgs.size = len;
    imgs.offset = 0;
    png_set_read_fn(png_ptr, &imgs, func_read_png);
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);
    img->width = png_get_image_width(png_ptr, info_ptr);
    img->height = png_get_image_height(png_ptr, info_ptr);
    img->depth = png_get_bit_depth(png_ptr, info_ptr);
    const png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    switch (color_type)
    {
    case PNG_COLOR_TYPE_RGB_ALPHA:
    {
        img->data = malloc(img->width * img->height * 4);
        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
        for(unsigned int i = 0; i < img->height; ++i)
        {
            const unsigned int row = img->height - i - 1;
            memcpy(img->data + (row * img->width * 4), row_pointers[i], img->width * 4);
        }
    }
        break;
    default:
    {}
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
}

void load_image_memory(struct image_unit* img, const void* buffer, const int len)
{
    switch (img->type)
    {
    case IMAGE_PNG:
        load_png(img, buffer, len);
        break;
    default:
    {}
    }
}