#ifndef PIONEERS_GAME_LUA_FUNCTIONS_H
#define PIONEERS_GAME_LUA_FUNCTIONS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

LUALIB_API int message(lua_State* l);
LUALIB_API int createWindow(lua_State* l);
LUALIB_API int windowShouldClose(lua_State* l);
LUALIB_API int windowEventsHandler(lua_State* l);
LUALIB_API int destroyWindow(lua_State* l);
LUALIB_API int loadImage(lua_State* l);
LUALIB_API int generateTexture(lua_State* l);
LUALIB_API int clearScene(lua_State* l);
LUALIB_API int drawImage(lua_State* l);

#endif