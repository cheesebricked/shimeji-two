#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "settings.h"
#include "shimeji.h"

// REQUIRES: SFML, WinAPI


Shimeji shimeji;

sf::Vector2i grabbedOffset;
bool grabbedWindow = false;

int main()
{
    initWindow();

    window.setFramerateLimit(60);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                    window.close();
                    break;
            
            case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                        grabbedWindow = true;
                    }
                    break;

            case sf::Event::MouseButtonReleased:
                
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    grabbedWindow = false;
                    shimeji.grabbed = false;
                }
                break;
                
            case sf::Event::MouseMoved:
                if (grabbedWindow)
                {
                    sf::Vector2i posSet = sf::Mouse::getPosition() + grabbedOffset;
                    window.setPosition(posSet);
                    shimeji.setWindowPos(posSet);
                    shimeji.grabbed = true;
                }
                break;
            }
        }

        // rgb (0, 2, 0, alpha) is our bg color. its the color windows will make transparent.
        // change this value to see the window size
        window.clear(sf::Color::Color(0,0,0,255));
        shimeji.update();
        shimeji.draw();
        window.display();
    }
}
