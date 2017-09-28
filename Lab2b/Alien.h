#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <stdlib.h>

class Character
{
public:
	Character(int type);
	~Character();

	void move();
	void changeVelocity();

	void draw(sf::RenderWindow& window);

private:

	float speed;
	bool pressed;
	int direction;
	int RIGHT = 1;
	int LEFT = 2;
	int UP = 3;
	int DOWN = 4;
	sf::Vector2f position;
	sf::Texture CharTexture;
	sf::Sprite Char;
};

