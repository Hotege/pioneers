#ifndef PIONEERS_GAME_LUA_BASE_H
#define PIONEERS_GAME_LUA_BASE_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "../../gatherer/gatherer.h"

void initialize_lua(struct script_node** list, int size);
void close_lua();

lua_State* get_l();

#endif