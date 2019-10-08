#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GLFWwindow* window = NULL;
unsigned char* icon = NULL;

void initialize_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void create_window(
    const char* title, int width, int height,
    const void* icon_data, const int icon_width, const int icon_height, const int icon_nums
)
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
    icon = (unsigned char*)malloc(icon_width * icon_height * 4 + 1);
    memset(icon, 0, icon_width * icon_height * 4 + 1);
    unsigned char* ptr = (unsigned char*)icon_data;
    for (int i = 0; i < icon_width; i++)
        for (int j = 0; j < icon_height; j++)
        {
            icon[((icon_height - 1 - j) * icon_width + i) * 4 + 0] = ptr[(j * icon_width + i) * icon_nums + 0];
            icon[((icon_height - 1 - j) * icon_width + i) * 4 + 1] = ptr[(j * icon_width + i) * icon_nums + 1];
            icon[((icon_height - 1 - j) * icon_width + i) * 4 + 2] = ptr[(j * icon_width + i) * icon_nums + 2];
            if (icon_nums == 4)
                icon[((icon_height - 1 - j) * icon_width + i) * 4 + 3] = ptr[(j * icon_width + i) * icon_nums + 3];
            else
                icon[((icon_height - 1 - j) * icon_width + i) * 4 + 3] = 255;
        }
    GLFWimage img = { (int)icon_width, (int)icon_height, icon };
    glfwSetWindowIcon(window, 1, &img);
}

void terminate_glfw()
{
    free(icon);
    icon = NULL;
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