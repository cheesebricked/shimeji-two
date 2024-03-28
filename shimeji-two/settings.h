#pragma once
#include <windows.h>
#include <SFML/Window.hpp>

// set videomode x and y to sprite image dimensions
sf::RenderWindow window(sf::VideoMode(620, 700), "My window", sf::Style::None);

void initWindow()
{

    SetWindowLong(FindWindowA(NULL, "My window"), GWL_EXSTYLE, GetWindowLong(FindWindowA(NULL, "My window"), GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(FindWindowA(NULL, "My window"), RGB(0, 2, 0), 0, LWA_COLORKEY);
}
