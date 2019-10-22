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
    const png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    switch (color_type)
    {
    case PNG_COLOR_TYPE_RGB:
    {
        img->nums = 3;
        img->data = malloc(img->width * img->height * img->nums);
        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
        for(unsigned int i = 0; i < img->height; ++i)
        {
            const unsigned int row = img->height - i - 1;
            memcpy(img->data + (row * img->width * img->nums), row_pointers[i], img->width * img->nums);
        }
    }
        break;
    case PNG_COLOR_TYPE_RGB_ALPHA:
    {
        img->nums = 4;
        img->data = malloc(img->width * img->height * img->nums);
        png_bytep* row_pointers = png_get_rows(png_ptr, info_ptr);
        for(unsigned int i = 0; i < img->height; ++i)
        {
            const unsigned int row = img->height - i - 1;
            memcpy(img->data + (row * img->width * img->nums), row_pointers[i], img->width * img->nums);
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

void save_bmp8(const struct image_unit* img, void** buffer, int* len)
{
    if (img->nums == 1)
    {
        int head_size = 14, info_size = 40, offset = head_size + info_size + 1024;
        *buffer = malloc(offset + img->width * img->height);
        memset(*buffer, 0, offset + img->width * img->height);
        *len = offset + img->width * img->height;
        int pos = 0;
        memcpy((*buffer) + pos, "BM", 2); pos += 2;
        int length = offset + img->width * img->height;
        memcpy((*buffer) + pos, &length, sizeof(int)); pos += sizeof(int);
        pos += 2;
        pos += 2;
        memcpy((*buffer) + pos, &offset, sizeof(int)); pos += sizeof(int);
        memcpy((*buffer) + pos, &info_size, sizeof(int)); pos += sizeof(int);
        memcpy((*buffer) + pos, &img->width, sizeof(int)); pos += sizeof(int);
        memcpy((*buffer) + pos, &img->height, sizeof(int)); pos += sizeof(int);
        short plane = 1;
        memcpy((*buffer) + pos, &plane, sizeof(short)); pos += sizeof(short);
        short bits = 8;
        memcpy((*buffer) + pos, &bits, sizeof(short)); pos += sizeof(short);
        pos += sizeof(int);
        pos += sizeof(int);
        pos += sizeof(int);
        pos += sizeof(int);
        int palatte_size = 256;
        memcpy((*buffer) + pos, &palatte_size, sizeof(int)); pos += sizeof(int);
        memcpy((*buffer) + pos, &palatte_size, sizeof(int)); pos += sizeof(int);
        unsigned char palatte[1024];
        memset(palatte, 0, 1024);
        int palatte_id[256];
        memset(palatte_id, -1, sizeof(int) * 256);
        int palatte_pos = 0;
        for (int y = 0; y < img->height; y++)
            for (int x = 0; x < img->width; x++)
            {
                unsigned char color = ((unsigned char*)(img->data))[(img->height - 1 - y) * img->width + x];
                if (palatte_id[color] == -1)
                {
                    palatte[palatte_pos * 4 + 0] = color;
                    palatte[palatte_pos * 4 + 1] = color;
                    palatte[palatte_pos * 4 + 2] = color;
                    palatte[palatte_pos * 4 + 3] = color;
                    palatte_id[color] = palatte_pos;
                    palatte_pos++;
                }
            }
        memcpy((*buffer) + pos, palatte, 1024); pos += 1024;
        unsigned char* indices = malloc(sizeof(unsigned char) * img->width * img->height);
        memset(indices, 0, img->width * img->height);
        for (int y = 0; y < img->height; y++)
            for (int x = 0; x < img->width; x++)
                if (palatte_id[0] != -1)
                    indices[y * img->width + x] = palatte_id[0];
                else
                    indices[y * img->width + x] = 0;
        for (int y = 0; y < img->height; y++)
            for (int x = 0; x < img->width; x++)
            {
                unsigned char color = ((unsigned char*)(img->data))[y * img->width + x];
                indices[y * img->width + x] = palatte_id[color];
            }
        memcpy((*buffer) + pos, indices, img->width * img->height); pos += img->width * img->height;
        free(indices);
        indices = NULL;
    }
}

void save_image_memory(const struct image_unit* img, void** buffer, int* len)
{
    switch (img->type)
    {
    case IMAGE_BMP8:
        save_bmp8(img, buffer, len);
        break;
    default:
    {}
    }
}