#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstdint>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class Shimeji
{
public:
	sf::Vector2i windowPosition;
	bool grabbed;
	int width, height, channels;

	Shimeji()
	{
		sprite.setOrigin((sf::Vector2f)idle.getSize() / 2.f);
		idle.loadFromFile(spritePath);
		grabbed = false;
		getPNGSize();
		initWindowShimeji();
		sprite.setTexture(idle);
		sprite.setPosition(0, 0);
		screenHeight = GetSystemMetrics(SM_CYSCREEN);
		taskbarHeight = getTaskbarHeight();
	}


	void update()
	{
		checkOnFloor();
		addGravity();
		walk();
		draw();
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

	sf::Texture idle;
	sf::Sprite sprite;
	bool facingRight = true;
	bool onFloor = false;

	int gravitySpeed = 7;
	int moveSpeed = 5;

	const char* spritePath = "sprites/testsprite.png";
	int screenHeight;
	int taskbarHeight;

	void initWindowShimeji()
	{
		window.setView(sf::View(sf::FloatRect(0, 0, width, height)));
		window.setSize(sf::Vector2u(width, height));
		windowPosition = window.getPosition();
	}

	void checkOnFloor()
	{
		onFloor = window.getPosition().y >= (screenHeight - height - taskbarHeight);
	}
	
	void addGravity()
	{
		if (!grabbed && !onFloor)
		{
			window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y + gravitySpeed));
		}
	}

	void walk() //  cahnge this to smth better
	{
		if (!grabbed && onFloor) 
		{
			if (rand() % 100 <= 40) // chance to move
			{
				if (rand() % 100 <= 10) // chance to flip
				{
					facingRight = !facingRight;
					tryFlip();
					moveSpeed *= -1;
				}
				window.setPosition(sf::Vector2i(window.getPosition().x + moveSpeed, window.getPosition().y));
			}
		}
	}

	// flips the sprite if sprite changes direction
	void tryFlip()
	{
		if (facingRight)
		{
			sprite.setTextureRect(sf::IntRect(0, 0, width, height));
		}
		else
		{
			sprite.setTextureRect(sf::IntRect(width, 0, -width, height));
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
