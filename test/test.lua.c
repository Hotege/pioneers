#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "../file/file.h"

const char lua_path[] = "scripts/info.lua";

lua_State* L;

int main(int argc, char const *argv[])
{
    L = luaL_newstate();
    luaopen_base(L);
    luaopen_table(L);
    luaopen_package(L);
    luaopen_io(L);
    luaopen_os(L);
    luaopen_string(L);
    luaL_openlibs(L);

    //luaL_dofile(L, "scripts/info.lua");
    if (argc >= 2)
    {
        printf("working path: %s\n", argv[1]);
        int len = strlen(argv[1]) + strlen(lua_path) + 2;
        char* path = (char*)malloc(sizeof(char) * len);
        memset(path, 0, sizeof(char) * len);
        strcpy(path, argv[1]);
        strcat(path, "/");
        strcat(path, lua_path);
        struct file_loader file;
        load_file(&file, path);
        luaL_dostring(L, file.data);

        lua_getglobal(L, "info");
        lua_pushstring(L, "showInfo");
        lua_gettable(L, -2);
        lua_pcall(L, 0, 0, 0);

        close_file(&file);
        free(path);
        path = NULL;
    }

    lua_close(L);
    return 0;
}