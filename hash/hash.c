#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hash_init(struct hash_node** table)
{
    *table = malloc(sizeof(struct hash_node) * HASH_SIZE);
    for (int i = 0; i < HASH_SIZE; i++)
    {
        (*table)[i].data = NULL;
        (*table)[i].next = NULL;
    }
}

int hash_get_key(const char* src)
{
    int k = 0;
    size_t s = strlen(src);
    for (size_t i = 0; i < s; i++)
        k = (((k & 0x7FF) << 5) + ((k & 0xF800) >> 11)) ^ src[i];
    return k;
}

void* hash_fetch(struct hash_node* table, const char* src)
{
    int k = hash_get_key(src);
    struct hash_node* p = table[k].next;
    while (p != NULL)
    {
        if (strcmp(p->key, src) == 0)
            return p->data;
        p = p->next;
    }
    return NULL;
}

void hash_free(struct hash_node** table)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        struct hash_node* p = (*table)[i].next;
        while (p != NULL)
        {
            free(p->key);
            p->key = NULL;
            struct hash_node* q = p->next;
            free(p);
            p = q;
        }
    }
    free(*table);
    *table = NULL;
}