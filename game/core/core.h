#ifndef PIONEERS_GAME_CORE_CORE_H
#define PIONEERS_GAME_CORE_CORE_H

#include <windows.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

void initialize_glfw();
void create_window(const char* title, int width, int height);
void terminate_glfw();

GLFWwindow* get_window();
HWND get_hwnd();

#endif