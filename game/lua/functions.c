#include "functions.h"
#include <GLFW/glfw3.h>
#include "global.h"
#include "../core/core.h"

LUALIB_API int message(lua_State* l)
{
    const char* msg = luaL_checkstring(l, -1);
    MessageBox(get_hwnd(), msg, __get_lua_string(l, "scene", "title"), 0);
}

LUALIB_API int createWindow(lua_State* l)
{
    create_window(
        __get_lua_string(l, "scene", "title"),
        __get_lua_int(l, "scene", "width"),
        __get_lua_int(l, "scene", "height")
    );
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