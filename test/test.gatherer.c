#include <stdio.h>
#include <stdlib.h>
#include "../file/file.h"
#include "../gatherer/gatherer.h"

int main(int argc, char const *argv[])
{
    printf("test process\n");
    struct file_loader file;
    load_file(&file, "scripts/info.lua");
    struct script_node* list = NULL;
    list = (struct script_node*)malloc(sizeof(struct script_node));
    list->title = "info.lua";
    list->title_size = 8;
    list->body = file.data;
    list->body_size = file.size;
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
    close_file(&file);
    return 0;
}