#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "../core/core.h"
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
    const float x = lua_tointeger(l, -4);
    const float y = lua_tointeger(l, -3);
    const float cx = lua_tointeger(l, -2);
    const float cy = lua_tointeger(l, -1);
    lua_pop(l, 4);
    lua_pushstring(l, "id");
    lua_gettable(l, -2);
    GLuint texture = lua_tointeger(l, -1);
    lua_pop(l, 1);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x, y);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(cx, y);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x, cy);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(cx, cy);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x, cy);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(cx, y);
    glEnd();
    return 0;
}