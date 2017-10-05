#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <stdlib.h>

class Player
{
public:
	Player();
	~Player();

	void move();
	void changeVelocity();
	sf::Vector2f position;
	sf::Vector2f velocity;
	void draw(sf::RenderWindow& window);

private:

	//0.0827 change by
	float rotation;

	float speed;
	bool pressed;
	int direction;
	int RIGHT = 1;
	int LEFT = 2;
	int UP = 3;
	int DOWN = 4;

	sf::Texture playerTexture;
	sf::Sprite player;
};

