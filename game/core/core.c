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
    RECT rtWindow;
    GetWindowRect(glfwGetWin32Window(window), &rtWindow);
    SetWindowPos(
        glfwGetWin32Window(window), HWND_TOP,
        (GetSystemMetrics(SM_CXSCREEN) - (rtWindow.right - rtWindow.left)) / 2,
        (GetSystemMetrics(SM_CYSCREEN) - (rtWindow.bottom - rtWindow.top)) / 2,
        0, 0, SWP_NOSIZE | SWP_NOZORDER
    );
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