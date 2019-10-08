#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../file/file.h"
#include "../crypt/crypt.h"

#define PATH_SIZE 800

int main(int argc, char const *argv[])
{
    printf("encrypt resources.\n");
    printf("path: %s\n", argv[1]);
    printf("file amount: %d\n", argc - 2);
    char file_name[PATH_SIZE];
    char output_file[PATH_SIZE];
    char output_path[PATH_SIZE];
    char file_path[PATH_SIZE];
    memset(file_name, 0, PATH_SIZE);
    memset(output_file, 0, PATH_SIZE);
    memset(output_path, 0, PATH_SIZE);
    memset(file_path, 0, PATH_SIZE);
    for (int i = 2; i < argc; i++)
    {
        memset(file_name, 0, PATH_SIZE);
        strcat(file_name, argv[i]);
        memset(output_file, 0, PATH_SIZE);
        strcat(output_file, file_name);
        strcat(output_file, ".hbc");
        memset(output_path, 0, PATH_SIZE);
        strcat(output_path, argv[1]);
        strcat(output_path, "/");
        strcat(output_path, output_file);
        memset(file_path, 0, PATH_SIZE);
        strcat(file_path, argv[1]);
        strcat(file_path, "/");
        strcat(file_path, file_name);
        struct file_loader file;
        load_file(&file, file_path);
        printf("file: %s\n", file_path);
        printf("output: %s\n", output_path);
        printf("size: %d\n", file.size);
        printf("key1: %s, key2: %s\n", file_name, output_file);
        unsigned char* result = (unsigned char*)malloc(file.size);
        encrypt_memory(
            result, file.data, file.size,
            (unsigned char*)file_name, strlen(file_name), (unsigned char*)output_file, strlen(output_file)
        );
        struct file_loader output;
        output.data = result;
        output.size = file.size;
        save_file(&output, output_path);
        free(result);
        result = NULL;
        close_file(&file);
    }
    return 0;
}