#include <stdio.h>
#include <stdlib.h>
#include "../file/file.h"
#include "core/core.h"
#include "lua/base.h"
#include "lua/global.h"
#include "../gatherer/gatherer.h"

int main(int argc, char const *argv[])
{
    // load file
    struct file_loader file;
    load_file(&file, "scripts.lzp");
    // load scripts
    int scripts_size = load_scripts_size(file.data);
    struct script_node** nodes = (struct script_node**)malloc(sizeof(struct script_node*) * scripts_size);
    for (int i = 0; i < scripts_size; i++)
        nodes[i] = NULL;
    uncompress_scripts(nodes, file.data, file.size);
    // initialize
    initialize_glfw();
    initialize_lua(nodes, scripts_size);
    // main function
    load_globals(get_l());
    execute_main(get_l());
    // close, terminate and free
    close_lua();
    terminate_glfw();
    for (int i = 0; i < scripts_size; i++)
    {
        free(nodes[i]->body);
        nodes[i]->body = NULL;
        free(nodes[i]);
        nodes[i] = NULL;
    }
    free(nodes);
    nodes = NULL;
    close_file(&file);
    return 0;
}