#ifndef PIONEERS_GAME_CORE_CORE_H
#define PIONEERS_GAME_CORE_CORE_H

#include <GL/glew.h>
#include <windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

void initialize_glfw();
void create_window(
    const char* title, int width, int height,
    const void* icon_data, const int icon_width, const int icon_height, const int icon_nums
);
void terminate_glfw();

GLFWwindow* get_window();
HWND get_hwnd();

#endif