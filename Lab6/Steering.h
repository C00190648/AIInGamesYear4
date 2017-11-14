#pragma once

#include <SFML\Graphics.hpp>

class Steering
{
public:
	Steering();
	~Steering();

	//this behavior makes the agent wander about randomly
	 sf::Vector2f Wander();
	 sf::Vector2f Evade();
	 sf::Vector2f Cohesion();
	 sf::Vector2f Separation();
	 sf::Vector2f Alignment();

private:

};

Steering::Steering()
{
}

Steering::~Steering()
{
}