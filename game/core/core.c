#include "core.h"

GLFWwindow* window = NULL;

void initialize_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void create_window(const char* title, int width, int height)
{
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void terminate_glfw()
{
    glfwTerminate();
}

GLFWwindow* get_window()
{
    return window;
}

HWND get_hwnd()
{
    return glfwGetWin32Window(window);
}