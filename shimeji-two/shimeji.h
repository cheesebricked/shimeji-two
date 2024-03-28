#pragma once
#include <SFML/Graphics.hpp>

class Shimeji
{
public:
	sf::Texture idle;
	sf::Sprite sprite;

	Shimeji()
	{
		idle.loadFromFile("sprites/testsprite.png");
		sprite.setTexture(idle);
		sprite.setPosition(0, 0);
	}

	void draw()
	{
		window.draw(sprite);
	}
	
private:
	


};
