#ifndef PIONEERS_HASH_HASH_H
#define PIONEERS_HASH_HASH_H

#define HASH_SIZE (1 << 16)

struct hash_node
{
    char* key;
    void* data;
    struct hash_node* next;
};

void hash_init(struct hash_node** table);
int hash_get_key(const char* src);
void* hash_fetch(struct hash_node* table, const char* src);
void hash_free(struct hash_node** table);

#endif