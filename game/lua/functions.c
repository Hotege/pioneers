#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLFW/glfw3.h>
#include "global.h"
#include "../core/core.h"
#include "../../file/file.h"
#include "../../crypt/crypt.h"
#include "../../image/image.h"

LUALIB_API int message(lua_State* l)
{
    const char* msg = luaL_checkstring(l, -1);
    MessageBox(get_hwnd(), msg, __get_lua_string(l, "scene", "title"), 0);
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
    free(img.data);
    img.data = NULL;
    close_file(&file);
    free(path);
    path = NULL;
    return 1;
}