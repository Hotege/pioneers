#ifndef PIONEERS_GAME_LUA_H
#define PIONEERS_GAME_LUA_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <GLFW/glfw3.h>

void load_globals(lua_State* l);

#define GetLuaMember(type, func, field, name) \
type __get_lua_##func(lua_State* l, const char* field, const char* name)

GetLuaMember(const char*, string, field, name);
GetLuaMember(int, int, field, name);

void execute_main(lua_State* l);

#endif