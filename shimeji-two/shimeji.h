#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdint>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Shimeji
{
public:
	sf::Texture idle;
	sf::Sprite sprite;
	sf::Vector2i windowPosition;
	bool grabbed;
	int width, height, channels;

	Shimeji()
	{
		idle.loadFromFile(spritePath);
		grabbed = false;
		getPNGSize();
		window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
		window.setSize(sf::Vector2u(width, height));
		windowPosition = window.getPosition();
		sprite.setTexture(idle);
		sprite.setPosition(0, 0);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);
		taskbarHeight = getTaskbarHeight();
	}


	void update()
	{
		addGravity();
	}
	

	void draw()
	{
		window.draw(sprite);
	}

	void setWindowPos(sf::Vector2i pos)
	{
		windowPosition = pos;
	}
	
private:

	int gravitySpeed = 7;
	const char* spritePath = "sprites/testsprite.png";
	int screenHeight;
	int taskbarHeight;
	
	void addGravity()
	{
		if (!grabbed && window.getPosition().y < (screenHeight - height - taskbarHeight))
		{
			window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y + gravitySpeed));
		}
	}
	
	void getPNGSize()
	{
		unsigned char* imageData = stbi_load(spritePath, &width, &height, &channels, STBI_default);

		if (!imageData) {
			std::cerr << "Failed to open image file." << std::endl;
			return;
		}

		stbi_image_free(imageData);
	}

};
