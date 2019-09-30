#ifndef PIONEERS_IMAGE_IMAGE_H
#define PIONEERS_IMAGE_IMAGE_H

enum IMAGE_TYPE
{
    IMAGE_UNKNOWN = 0,
    IMAGE_PNG
};

struct image_unit
{
    void* data; // BGRA
    int width, height;
    int depth;
    enum IMAGE_TYPE type;
};

void load_image_memory(struct image_unit* img, const void* buffer, const int len);

#endif