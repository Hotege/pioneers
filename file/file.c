#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_file(struct file_loader* fl, const char* path)
{
    FILE* file = fopen(path, "rb");
    if (!file)
        return 0;
    fseek(file, 0, SEEK_END);
    fl->size = ftell(file);
    fseek(file, 0, SEEK_SET);
    fl->data = (unsigned char*)malloc(sizeof(unsigned char) * (fl->size + 1));
    memset(fl->data, 0, fl->size + 1);
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

void save_wfile(struct file_loader* fl, const wchar_t* path)
{
    FILE* file = _wfopen(path, L"wb");
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