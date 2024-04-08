#pragma once
#include <windows.h>
#include <SFML/Window.hpp>

int WIDTH = 0;
int HEIGHT = 0;

// set videomode x and y to sprite image dimensions
sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "My window", sf::Style::None);

HWND windowHandle;

void initWindow()
{
    windowHandle = FindWindowA(NULL, "My window");

    SetWindowLong(windowHandle, GWL_EXSTYLE, GetWindowLong(windowHandle, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(windowHandle, RGB(0, 2, 0), 0, LWA_COLORKEY);
}

UINT getTaskbarHeight() {
    APPBARDATA abd;
    abd.cbSize = sizeof(APPBARDATA);
    UINT taskbarHeight = 0;

    // Get the taskbar's size and position
    if (SHAppBarMessage(ABM_GETTASKBARPOS, &abd)) {
        if (abd.uEdge == ABE_LEFT || abd.uEdge == ABE_RIGHT) {
            // Vertical taskbar
            taskbarHeight = abd.rc.right - abd.rc.left;
        }
        else {
            // Horizontal taskbar
            taskbarHeight = abd.rc.bottom - abd.rc.top;
        }
    }

    return taskbarHeight;
}