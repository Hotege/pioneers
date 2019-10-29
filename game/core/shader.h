#ifndef PIONEERS_GAME_CORE_SHADER
#define PIONEERS_GAME_CORE_SHADER

#include <GL/glew.h>

struct shader_field
{
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint program;
};

void shader_hash_init();
void shader_hash_push(const char* key, const char* vs, const char* fs);
struct shader_field* shader_fetch(const char* name);
void shader_hash_free();

#endif