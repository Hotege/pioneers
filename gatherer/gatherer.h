#ifndef PIONEERS_GATHERER_GATHERER_H
#define PIONEERS_GATHERER_GATHERER_H

struct script_node
{
    const char* title;
    int title_size;
    char* body;
    int body_size;
    struct script_node* next;
};

int get_list_size(struct script_node* ptr_node);
void append_list(struct script_node** list, struct script_node* ptr_node);

unsigned long compress_scripts_bound(struct script_node* ptr_node);
void compress_scripts(void* dest, unsigned long* destLen, struct script_node* ptr_node);
int load_scripts_size(const void* data);
void uncompress_scripts(struct script_node** nodes, const void* data, int fs);

#endif