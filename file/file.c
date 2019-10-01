#include "file.h"
#include <stdio.h>
#include <stdlib.h>

int load_file(struct file_loader* fl, const char* path)
{
    FILE* file = fopen(path, "rb");
    if (!file)
        return 0;
    fseek(file, 0, SEEK_END);
    fl->size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fl->data = (unsigned char*)malloc(sizeof(unsigned char) * fl->size);
    fread(fl->data, fl->size, sizeof(unsigned char), file);
    fclose(file);
    return 1;
}

void save_file(struct file_loader* fl, const char* path)
{
    FILE* file = fopen(path, "wb");
    fwrite(fl->data, fl->size, 1, file);
    fclose(file);
}

void close_file(struct file_loader* fl)
{
    if (fl != NULL)
    {
        free(fl->data);
        fl->data = NULL;
    }
}