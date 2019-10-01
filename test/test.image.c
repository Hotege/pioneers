#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../image/image.h"

int main(int argc, char const *argv[])
{
    FILE* file = fopen("test.png", "rb");
    fseek(file, 0, SEEK_END);
    long fs = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * fs);
    fread(data, fs, sizeof(unsigned char), file);
    fclose(file);
    printf("file size: %d\n", fs);
    struct image_unit img = { 0 };
    img.type = IMAGE_PNG;
    load_image_memory(&img, data, fs);
    printf("%d\t%d\n", img.width, img.height);
    printf(
        "%d\t%d\t%d\n",
        ((unsigned char*)(img.data))[(8 * img.height + 0) * img.nums + 0],
        ((unsigned char*)(img.data))[(8 * img.height + 0) * img.nums + 1],
        ((unsigned char*)(img.data))[(8 * img.height + 0) * img.nums + 2]//,
        //((unsigned char*)(img.data))[(8 * img.height + 0) * img.nums + 3]
    );
    printf(
        "%d\t%d\t%d\n",
        ((unsigned char*)(img.data))[((img.width - 1) * img.height + (img.height - 1)) * img.nums + 0],
        ((unsigned char*)(img.data))[((img.width - 1) * img.height + (img.height - 1)) * img.nums + 1],
        ((unsigned char*)(img.data))[((img.width - 1) * img.height + (img.height - 1)) * img.nums + 2]//,
        //((unsigned char*)(img.data))[((img.width - 1) * img.height + (img.height - 1)) * img.nums + 3]
    );
    free(img.data);
    img.data = NULL;
    free(data);
    data = NULL;
    return 0;
}