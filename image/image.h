#ifndef PIONEERS_IMAGE_IMAGE_H
#define PIONEERS_IMAGE_IMAGE_H

enum IMAGE_TYPE
{
    IMAGE_UNKNOWN = 0,
    IMAGE_PNG,
    IMAGE_BMP4,
    IMAGE_BMP8,
    IMAGE_BMP24,
};

struct image_unit
{
    void* data; // BGRA
    int width, height;
    int nums; // amount of colors
    enum IMAGE_TYPE type;
};

void load_image_memory(struct image_unit* img, const void* buffer, const int len);
void save_image_memory(const struct image_unit* img, void** buffer, int* len);

#endif