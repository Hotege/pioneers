#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "../gatherer/gatherer.h"

#define EXPAND_SIZE 200

lua_State* L;

void filecat(char* dest, int destLen, const char* path, const char* filename)
{
    memset(dest, 0, sizeof(char) * destLen);
    strcpy(dest, path);
    strcat(dest, "/");
    strcat(dest, filename);
}

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
    printf("size of parameter(s): %d\n", argc);
    if (argc >= 3)
    {
        printf("scripts directory: %s\n", argv[1]);
        printf("output path: %s\n", argv[2]);
        if (!access(argv[2], F_OK))
        {
            printf("cannot create output file: %s, file exists.\n", argv[2]);
            goto FINISH;
        }
        int len = strlen(argv[1]) + EXPAND_SIZE;
        char* full = (char*)malloc(sizeof(char) * len);
        memset(full, 0, sizeof(char) * len);
        strcpy(full, argv[1]);
        strcat(full, "/");
        strcat(full, "SEQUENCE");
        luaL_dofile(L, full);
        lua_getglobal(L, "size");
        lua_isnumber(L, -1);
        int size = lua_tonumber(L, -1);
        printf("files amount: %d\n", size);
        struct script_node* list = NULL;
        int code_size = 0;
        for (int i = 0; i < size; i++)
        {
            lua_getglobal(L, "sequence");
            lua_pushinteger(L, i);
            lua_gettable(L, -2);
            const char* name = lua_tostring(L, -1);
            filecat(full, len, argv[1], name);

            FILE* f = fopen(full, "rb");
            if (!f)
            {
                printf("error: cannot find file %s\n", name);
                continue;
            }
            fseek(f, 0, SEEK_END);
            long fs = ftell(f);
            fseek(f, 0, SEEK_SET);
            char* d = (char*)malloc(sizeof(char) * fs);
            fread(d, fs, sizeof(char), f);
            fclose(f);
            printf("full path: %s, size: %d\n", full, fs);
            struct script_node* n = (struct script_node*)malloc(sizeof(struct script_node));
            n->title = name;
            n->title_size = strlen(name);
            n->body = d;
            n->body_size = fs;
            n->next = NULL;
            append_list(&list, n);
            code_size += fs;
        }
        printf("list size: %d\n", get_list_size(list));
        unsigned long bound = compress_scripts_bound(list);
        printf("codes size: %d\n", code_size);
        printf("bound: %lu\n", bound);
        unsigned char* dest = (unsigned char*)malloc(sizeof(unsigned char) * bound);
        compress_scripts(dest, &bound, list);
        printf("result size: %lu\n", bound);
        printf("compress rate: %lf\n", (double)(bound) / (double)(code_size));
        FILE* output = fopen(argv[2], "wb");
        fwrite(dest, bound, sizeof(unsigned char), output);
        fclose(output);
        printf("file %s saved.\n", argv[2]);
        free(dest);
        dest = NULL;
        free(full);
        full = NULL;
        struct script_node* p = list;
        while (p != NULL)
        {
            free(p->body);
            p->body = NULL;
            struct script_node* q = p->next;
            free(p);
            p = q;
        }
    }
FINISH:
    lua_close(L);
    return 0;
}