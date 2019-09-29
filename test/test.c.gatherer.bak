#include <stdio.h>
#include <stdlib.h>
#include "../gatherer/gatherer.h"

int main(int argc, char const *argv[])
{
    printf("test process\n");
    FILE* f = fopen("scripts/info.lua", "rb");
    fseek(f, 0, SEEK_END);
    long fs = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* data = (char*)malloc(sizeof(char) * fs);
    fread(data, fs, sizeof(char), f);
    fclose(f);
    struct script_node* list = NULL;
    list = (struct script_node*)malloc(sizeof(struct script_node));
    list->title = "info.lua";
    list->title_size = 8;
    list->body = data;
    list->body_size = fs;
    list->next = NULL;
    printf("size of list: %d\n", get_list_size(list));
    unsigned long bound = compress_scripts_bound(list);
    printf("origin size: %lu\n", fs);
    printf("bound: %lu\n", bound);
    unsigned char* dest = (unsigned char*)malloc(sizeof(unsigned char) * bound);
    compress_scripts(dest, &bound, list);
    printf("result size: %lu\n", bound);
    free(dest);
    dest = NULL;
    free(list);
    list = NULL;
    free(data);
    data = NULL;
    return 0;
}