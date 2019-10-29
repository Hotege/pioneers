#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "global.h"
#include "../core/core.h"
#include "../core/shader.h"
#include "../font/font.h"
#include "../../file/file.h"
#include "../../crypt/crypt.h"
#include "../../image/image.h"
#include <GLFW/glfw3.h>

LUALIB_API int message(lua_State* l)
{
    const char* msg = luaL_checkstring(l, -1);
    MessageBox(get_hwnd(), msg, __get_lua_string(l, "scene", "title"), 0);
    return 0;
}

LUALIB_API int shadersInitialize(lua_State* l)
{
    shader_hash_init();
    lua_pushnil(l);
    while (lua_next(l, -2))
    {
        const char* program_name = lua_tostring(l, -2);
        const char* vertex_shader = NULL;
        const char* fragment_shader = NULL;
        if (lua_isstring(l, -2) && lua_istable(l, -1))
        {
            lua_pushnil(l);
            while (lua_next(l, -2))
            {
                if (lua_isstring(l, -2) && lua_isstring(l, -1))
                {
                    if (strcmp(lua_tostring(l, -2), "vertexShader") == 0)
                        vertex_shader = lua_tostring(l, -1);
                    if (strcmp(lua_tostring(l, -2), "fragmentShader") == 0)
                        fragment_shader = lua_tostring(l, -1);
                }
                lua_pop(l, 1);
            }
        }
        shader_hash_push(program_name, vertex_shader, fragment_shader);
        lua_pop(l, 1);
    }
    return 0;
}

LUALIB_API int shadersTerminate(lua_State* l)
{
    shader_hash_free();
    return 0;
}

LUALIB_API int fontInitialize(lua_State* l)
{
    const char* filename = luaL_checkstring(l, -2);
    const int encrypted = lua_toboolean(l, -1);
    font_initialize(filename, encrypted);
    return 0;
}

LUALIB_API int fontTerminate(lua_State* l)
{
    font_terminate();
    return 0;
}

LUALIB_API int createWindow(lua_State* l)
{
    lua_pushstring(l, "width");
    lua_gettable(l, -2);
    int icon_width = lua_tointeger(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "height");
    lua_gettable(l, -2);
    int icon_height = lua_tointeger(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "nums");
    lua_gettable(l, -2);
    int icon_nums = lua_tointeger(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "data");
    lua_gettable(l, -2);
    unsigned char* data = (unsigned char*)malloc(icon_width * icon_height * icon_nums);
    for (int i = 0; i < icon_width * icon_height * icon_nums; i += 4)
    {
        lua_pushinteger(l, i);
        lua_gettable(l, -2);
        *((int*)(data + i)) = lua_tointeger(l, -1);
        lua_pop(l, 1);
    }
    lua_pop(l, 1);
    create_window(
        __get_lua_string(l, "scene", "title"),
        __get_lua_int(l, "scene", "width"),
        __get_lua_int(l, "scene", "height"),
        data, icon_width, icon_height, icon_nums
    );
    free(data);
    data = NULL;
    return 0;
}

LUALIB_API int windowShouldClose(lua_State* l)
{
    int result = glfwWindowShouldClose(get_window());
    lua_pushboolean(l, result);
    return 1;
}

LUALIB_API int windowEventsHandler(lua_State* l)
{
    glfwPollEvents();
    glfwSwapBuffers(get_window());
    return 0;
}

LUALIB_API int destroyWindow(lua_State* l)
{
    glfwDestroyWindow(get_window());
    return 0;
}

LUALIB_API int loadImage(lua_State* l)
{
    const char* filename = luaL_checkstring(l, -2);
    const int encrypted = lua_toboolean(l, -1);
    char* path = (char*)malloc(strlen(filename) + 6);
    memset(path, 0, strlen(filename) + 6);
    strcat(path, filename);
    if (encrypted)
        strcat(path, ".hbc");
    struct file_loader file;
    load_file(&file, path);
    struct image_unit img;
    img.type = IMAGE_PNG;
    if (encrypted)
    {
        unsigned char* decrypt = (unsigned char*)malloc(file.size);
        memset(decrypt, 0, file.size);
        decrypt_memory(
            decrypt, (unsigned char*)file.data, file.size,
            filename, strlen(filename), path, strlen(path)
        );
        load_image_memory(&img, decrypt, file.size);
        free(decrypt);
        decrypt = NULL;
    }
    else
        load_image_memory(&img, file.data, file.size);
    unsigned char test[4] = { 128, 128, 128, 128 };
    lua_newtable(l);
    lua_pushstring(l, "width");
    lua_pushinteger(l, img.width);
    lua_settable(l, -3);
    lua_pushstring(l, "height");
    lua_pushinteger(l, img.height);
    lua_settable(l, -3);
    lua_pushstring(l, "nums");
    lua_pushinteger(l, img.nums);
    lua_settable(l, -3);
    lua_pushstring(l, "data");
    lua_newtable(l);
    for (int i = 0; i < img.width * img.height * img.nums; i += sizeof(int))
    {
        lua_pushinteger(l, i);
        lua_pushinteger(l, *((int*)(img.data + i)));
        lua_settable(l, -3);
    }
    lua_settable(l, -3);
    lua_pushstring(l, "generateTexture");
    lua_pushcfunction(l, texture_generateTexture);
    lua_settable(l, -3);
    free(img.data);
    img.data = NULL;
    close_file(&file);
    free(path);
    path = NULL;
    return 1;
}

LUALIB_API int texture_generateTexture(lua_State* l)
{
    lua_pushstring(l, "width");
    lua_gettable(l, -2);
    int width = lua_tointeger(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "height");
    lua_gettable(l, -2);
    int height = lua_tointeger(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "nums");
    lua_gettable(l, -2);
    int nums = lua_tointeger(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "data");
    lua_gettable(l, -2);
    unsigned char* data = (unsigned char*)malloc(width * height * nums);
    for (int i = 0; i < width * height * nums; i += 4)
    {
        lua_pushinteger(l, i);
        lua_gettable(l, -2);
        *((int*)(data + i)) = lua_tointeger(l, -1);
        lua_pop(l, 1);
    }
    lua_pop(l, 1);
    GLuint texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    if (nums == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    if (nums == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    free(data);
    data = NULL;
    lua_newtable(l);
    lua_pushstring(l, "id");
    lua_pushinteger(l, texture);
    lua_settable(l, -3);
    lua_pushstring(l, "display");
    lua_pushcfunction(l, texture_display);
    lua_settable(l, -3);
    return 1;
}

LUALIB_API int clearScene(lua_State* l)
{
    const float r = lua_tonumber(l, -4);
    const float g = lua_tonumber(l, -3);
    const float b = lua_tonumber(l, -2);
    const float a = lua_tonumber(l, -1);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
    glClearDepth(1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    return 0;
}

LUALIB_API int texture_display(lua_State* l)
{
    const float x = lua_tonumber(l, -4);
    const float y = lua_tonumber(l, -3);
    const float cx = lua_tonumber(l, -2);
    const float cy = lua_tonumber(l, -1);

    static float display2d_position[12];
    display2d_position[0] = x;
    display2d_position[1] = y;
    display2d_position[2] = cx;
    display2d_position[3] = y;
    display2d_position[4] = x;
    display2d_position[5] = cy;
    display2d_position[6] = cx;
    display2d_position[7] = cy;
    display2d_position[8] = x;
    display2d_position[9] = cy;
    display2d_position[10] = cx;
    display2d_position[11] = y;
    static float display2d_texcoord[] = {
        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    };
    static unsigned int display2d_indices[] = { 0, 1, 2, 3, 4, 5, };

    struct shader_field* shader = shader_fetch("display2D");
    glUseProgram(shader->program);
    GLint position_location = glGetAttribLocation(shader->program, "positionInput");
    glEnableVertexAttribArray(position_location);
    glVertexAttribPointer(position_location, 2, GL_FLOAT, GL_FALSE, 0, display2d_position);
    GLint texcoord_location = glGetAttribLocation(shader->program, "texCoordInput");
    glEnableVertexAttribArray(texcoord_location);
    glVertexAttribPointer(texcoord_location, 2, GL_FLOAT, GL_FALSE, 0, display2d_texcoord);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, lua_tointeger(l, -1));
    glUniform1i(glGetUniformLocation(shader->program, "textureInput"), 0);
    glDrawElements(GL_TRIANGLES, sizeof(display2d_indices) / sizeof(unsigned int), GL_UNSIGNED_INT, display2d_indices);
    return 0;
}

void char2wchar(const char* src, wchar_t* dst)
{
    setlocale(LC_ALL, "");
    mbstowcs(dst, src, strlen(src) + 1);
}

LUALIB_API int generateTextTexture(lua_State* l)
{
    lua_pushstring(l, "r");
    lua_gettable(l, -2);
    float font_r = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "g");
    lua_gettable(l, -2);
    float font_g = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "b");
    lua_gettable(l, -2);
    float font_b = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "a");
    lua_gettable(l, -2);
    float font_a = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pop(l, 1);
    lua_pushstring(l, "r");
    lua_gettable(l, -2);
    float back_r = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "g");
    lua_gettable(l, -2);
    float back_g = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "b");
    lua_gettable(l, -2);
    float back_b = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pushstring(l, "a");
    lua_gettable(l, -2);
    float back_a = lua_tonumber(l, -1);
    lua_pop(l, 1);
    lua_pop(l, 1);
    const char* text = luaL_checkstring(l, -2);
    const int size = lua_tointeger(l, -1);
    int ws = mbstowcs(NULL, text, 0) + 1;
    wchar_t* wtext = malloc(sizeof(wchar_t) * ws);
    char2wchar(text, wtext);
    unsigned char* buffer = NULL;
    int render_width = 0, render_height = 0;
    font_render(&buffer, &render_width, &render_height, wtext, size);
    free(buffer);
    buffer = NULL;
    free(wtext);
    wtext = NULL;
    lua_newtable(l);
    lua_pushstring(l, "id");
    lua_pushinteger(l, 0);
    lua_settable(l, -3);
    lua_pushstring(l, "display");
    lua_pushcfunction(l, texture_display);
    lua_settable(l, -3);
    return 1;
}