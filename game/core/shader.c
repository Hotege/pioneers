#include "shader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../hash/hash.h"

struct hash_node* table = NULL;

void shader_hash_init()
{
    hash_init(&table);
}

void shader_hash_push(const char* key, const char* vs, const char* fs)
{
    int k = hash_get_key(key);
    struct hash_node* ptr = &table[k];
    while (ptr->next != NULL)
        ptr = ptr->next;
    struct hash_node* append = malloc(sizeof(struct hash_node));
    append->data = malloc(sizeof(struct shader_field));
    append->key = malloc(strlen(key) + 1);
    memset(append->key, 0, strlen(key) + 1);
    strcpy(append->key, key);
    memset(append->data, 0, sizeof(struct shader_field));
    ((struct shader_field*)(append->data))->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(((struct shader_field*)(append->data))->vertex_shader, 1, &vs, NULL);
    glCompileShader(((struct shader_field*)(append->data))->vertex_shader);
    ((struct shader_field*)(append->data))->fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(((struct shader_field*)(append->data))->fragment_shader, 1, &fs, NULL);
    glCompileShader(((struct shader_field*)(append->data))->fragment_shader);
    ((struct shader_field*)(append->data))->program = glCreateProgram();
    glAttachShader(((struct shader_field*)(append->data))->program, ((struct shader_field*)(append->data))->vertex_shader);
    glAttachShader(((struct shader_field*)(append->data))->program, ((struct shader_field*)(append->data))->fragment_shader);
    glLinkProgram(((struct shader_field*)(append->data))->program);
    append->next = NULL;
    ptr->next = append;
}

struct shader_field* shader_fetch(const char* name)
{
    return (struct shader_field*)(hash_fetch(table, name));
}

void shader_hash_free()
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        struct hash_node* ptr = &table[i];
        while (ptr->next != NULL)
        {
            free(ptr->data);
            ptr->data = NULL;
            ptr = ptr->next;
        }
    }
    hash_free(&table);
}