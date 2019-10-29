#ifndef PIONEERS_GAME_LUA_FUNCTIONS_H
#define PIONEERS_GAME_LUA_FUNCTIONS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

LUALIB_API int message(lua_State* l);
LUALIB_API int shadersInitialize(lua_State* l);
LUALIB_API int shadersTerminate(lua_State* l);
LUALIB_API int fontInitialize(lua_State* l);
LUALIB_API int fontTerminate(lua_State* l);
LUALIB_API int createWindow(lua_State* l);
LUALIB_API int windowShouldClose(lua_State* l);
LUALIB_API int windowEventsHandler(lua_State* l);
LUALIB_API int destroyWindow(lua_State* l);
LUALIB_API int loadImage(lua_State* l);
LUALIB_API int texture_generateTexture(lua_State* l);
LUALIB_API int clearScene(lua_State* l);
LUALIB_API int texture_display(lua_State* l);
LUALIB_API int generateTextTexture(lua_State* l);

#endif