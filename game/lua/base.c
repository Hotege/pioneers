#include "base.h"

lua_State* L;

void initialize_lua(struct script_node** list, int size)
{
    L = luaL_newstate();
    luaopen_base(L);
    luaopen_table(L);
    luaopen_package(L);
    luaopen_io(L);
    luaopen_os(L);
    luaopen_string(L);
    luaL_openlibs(L);
    for (int i = 0; i < size; i++)
        luaL_dostring(L, list[i]->body);
}

void close_lua()
{
    lua_close(L);
}

lua_State* get_l()
{
    return L;
}