#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <stdlib.h>
#include "Player.h"

class alien
{
public:
	alien(int type, float setSpeed);
	~alien();

	void move();
	void seek(sf::Vector2f target);
	//void changeVelocity();
	float getOrientation();
	void wander(sf::Vector2f target);
	void arrive(sf::Vector2f target);
	void pursue(sf::Vector2f target, sf::Vector2f targetVelocity);
	void draw(sf::RenderWindow& window);

	void collisionAvoidance();
	float getMag(sf::Vector2f velocity);

private:

	float speed;
	bool pressed;
	float rotation;
	float maxSpeed = 5;
	float timeToTarget;
	float radius = 70;
	int RIGHT = 1;
	int LEFT = 2;
	int UP = 3;
	int DOWN = 4;
	float maxRotation = 10;
	int timer;
	float wanderR;
	sf::Vector2f position;
	sf::Texture CharTexture;
	sf::Vector2f velocity;
	sf::Sprite Char;
	sf::Vector2f direction;
	float orientation;
	float maxTimePrediction = 0.8;
	float timePrediction = 0.8;

	sf::Vector2f wanderOffset;
	float wanderRadius;
	float wanderRate;
	float wanderOrientation;
	sf::Vector2f targetOrientation;



};

