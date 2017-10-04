#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <stdlib.h>
#include "Player.h"

class alien
{
public:
	alien(int type);
	~alien();

	void move();
	void seek(Player target);
	//void changeVelocity();
	float getOrientation();
	void wander(Player target);
	void draw(sf::RenderWindow& window);
	float getMag(sf::Vector2f velocity);

private:

	float speed;
	bool pressed;
	int direction;
	float rotation;
	float maxSpeed = 2;
	int RIGHT = 1;
	int LEFT = 2;
	int UP = 3;
	int DOWN = 4;
	float maxRotation = 60;
	sf::Vector2f position;
	sf::Texture CharTexture;
	sf::Vector2f velocity;
	sf::Sprite Char;
	float orientation;

};

