#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file/file.h"
#include "../image/image.h"

int main(int argc, char const *argv[])
{
    struct file_loader file;
    load_file(&file, "test.png");
    printf("file size: %d\n", file.size);
    struct image_unit img = { 0 };
    img.type = IMAGE_PNG;
    load_image_memory(&img, file.data, file.size);
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
    close_file(&file);
    return 0;
}