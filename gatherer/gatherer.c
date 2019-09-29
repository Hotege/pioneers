#include "gatherer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

int get_list_size(struct script_node* ptr_node)
{
    int size = 0;
    struct script_node* ptr = ptr_node;
    while (ptr != NULL)
    {
        size++;
        ptr = ptr->next;
    }
    return size;
}

void append_list(struct script_node** list, struct script_node* ptr_node)
{
    if (*list == NULL)
    {
        *list = ptr_node;
        return;
    }
    struct script_node* pl = *list;
    while (pl->next != NULL)
        pl = pl->next;
    pl->next = ptr_node;
}

unsigned long compress_scripts_bound(struct script_node* ptr_node)
{
    unsigned long result = sizeof(int);
    struct script_node* ptr = ptr_node;
    while (ptr != NULL)
    {
        uLong bound = compressBound(ptr->body_size);
        result += sizeof(int) * 3 + ptr->title_size + bound;
        ptr = ptr->next;
    }
    return result;
}

void compress_scripts(void* dest, unsigned long* destLen, struct script_node* ptr_node)
{
    int size = get_list_size(ptr_node);
    unsigned long bound = compress_scripts_bound(ptr_node);
    struct script_node* ptr = ptr_node;
    unsigned char* ptr_dest = (unsigned char*)dest;
    unsigned long pos = 0;
    *((int*)(ptr_dest + pos)) = size;
    pos += sizeof(int);
    while (ptr != NULL)
    {
        *((int*)(ptr_dest + pos)) = ptr->title_size;
        pos += sizeof(int);
        memcpy(ptr_dest + pos, ptr->title, ptr->title_size);
        pos += ptr->title_size;
        *((int*)(ptr_dest + pos)) = ptr->body_size;
        pos += sizeof(int);
        uLong bound_ptr = compressBound(ptr->body_size);
        unsigned char* d = (unsigned char*)malloc(sizeof(unsigned char) * bound_ptr);
        uLong destLen_ptr = bound_ptr;
        compress(d, &destLen_ptr, ptr->body, ptr->body_size);
        *((int*)(ptr_dest + pos)) = destLen_ptr;
        pos += sizeof(int);
        memcpy(ptr_dest + pos, d, destLen_ptr);
        pos += destLen_ptr;
        free(d);
        d = NULL;
        ptr = ptr->next;
    }
    *destLen = pos;
}

int load_scripts_size(const void* data)
{
    return *(int*)data;
}

void uncompress_script(struct script_node* ptr_node, void* src, int srcLen, int destLen)
{
    uLong len = destLen;
    char* dest = (char*)malloc(sizeof(char) * destLen + 1);
    memset(dest, 0, sizeof(char) * destLen + 1);
    uncompress(dest, &len, src, srcLen);
    ptr_node->body = dest;
    ptr_node->body_size = (int)len;
}

void uncompress_scripts(struct script_node** nodes, const void* data, int fs)
{
    int count = 0;
    long pos = sizeof(int);
    while (pos < fs)
    {
        int name_size = *(int*)(data + pos);
        pos += sizeof(int);
        char* name = (char*)malloc(sizeof(char) * name_size + 1);
        memset(name, 0, sizeof(char) * name_size + 1);
        memcpy(name, (char*)(data + pos), name_size);
        pos += name_size;
        int src_size = *(int*)(data + pos);
        pos += sizeof(int);
        int dest_size = *(int*)(data + pos);
        pos += sizeof(int);
        unsigned char* compressed = (char*)malloc(sizeof(char) * dest_size);
        memcpy(compressed, (unsigned char*)(data + pos), dest_size);
        pos += dest_size;
        nodes[count] = (struct script_node*)malloc(sizeof(struct script_node));
        nodes[count]->body = NULL;
        uncompress_script(nodes[count], compressed, dest_size, src_size);
        free(compressed);
        compressed = NULL;
        free(name);
        name = NULL;
        count++;
    }
}