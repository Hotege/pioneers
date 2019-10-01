#ifndef PIONEERS_FILE_FILE_H
#define PIONEERS_FILE_FILE_H

struct file_loader
{
    void* data;
    long size;
};

int load_file(struct file_loader* fl, const char* path);
void save_file(struct file_loader* fl, const char* path);
void close_file(struct file_loader* fl);

#endif