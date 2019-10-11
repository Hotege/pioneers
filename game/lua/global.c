#include "global.h"
#include <stdio.h>
#include "functions.h"

// global variables and functions in lua files

void load_globals(lua_State* l)
{
    // window
    lua_pushinteger(l, (int)get_window());
    lua_setglobal(l, "window");
    // functions
    lua_pushcfunction(l, message);
    lua_setglobal(l, "message");
    lua_pushcfunction(l, createWindow);
    lua_setglobal(l, "createWindow");
    lua_pushcfunction(l, windowShouldClose);
    lua_setglobal(l, "windowShouldClose");
    lua_pushcfunction(l, windowEventsHandler);
    lua_setglobal(l, "windowEventsHandler");
    lua_pushcfunction(l, destroyWindow);
    lua_setglobal(l, "destroyWindow");
    lua_pushcfunction(l, loadImage);
    lua_setglobal(l, "loadImage");
    lua_pushcfunction(l, clearScene);
    lua_setglobal(l, "clearScene");
}

GetLuaMember(const char*, string, fields, name)
{
    lua_getglobal(l, fields);
    lua_pushstring(l, name);
    lua_gettable(l, -2);
    return lua_tostring(l, -1);
}

GetLuaMember(int, int, fields, name)
{
    lua_getglobal(l, fields);
    lua_pushstring(l, name);
    lua_gettable(l, -2);
    return lua_tonumber(l, -1);
}

void execute_main(lua_State* l)
{
    lua_getglobal(l, "main");
    lua_pcall(l, 0, 0, 0);
}