#include "Alien.h"
#include <math.h>

alien::alien(int type)
{
	direction = rand() % 5 + 1;

	//direction = 3;

	if (type == 1)
	{
		CharTexture.loadFromFile("alien.png");
		Char.setTexture(CharTexture);
		Char.setOrigin(25, 42);

		position.x = 500;
		position.y = 500;
		speed = 2;
		//Char.setRotation(Char.getRotation());

		//rotation = Char.getRotation();
		//orientation = getOrientation();
	}
}

alien::~alien()
{
}

void alien::move()
{

	position = position + velocity;


	if (position.x > 1000)
	{
		position.x = 5;
	}

	if (position.x < -50)
	{
		position.x = 990;
	}

	if (position.y > 1000)
	{
		position.y = 5;
	}

	if (position.y < -50)
	{
		position.y = 990;
	}

}



void alien::draw(sf::RenderWindow& window)
{
	Char.setPosition(position.x, position.y);
	Char.setRotation(orientation);
	window.draw(Char);
}

void alien::seek(Player target)
{

	velocity = target.position - position;
	float temp = getMag(velocity);
	velocity = velocity / temp;
	velocity = velocity * maxSpeed;
	position = position + velocity;
	orientation = getOrientation();
	orientation = orientation * 180 / 3.14;

	
}



float alien::getOrientation()
{
	if (sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y)) > 0)
	{
		return atan2(-velocity.x ,velocity.y);
	}
	else
	{
		return orientation;
	}
}

float alien::getMag(sf::Vector2f velocity)
{
	float temp = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	return temp;
}


void alien::wander(Player target)
{
	float temp;
	velocity = target.position - position;
	temp = getMag(velocity);
	velocity = velocity / temp;
	orientation = getOrientation();
	//orientation = orientation * 180 / 3.14;

	//orientation = (orientation + maxRotation) * (rand() % 3 - 1);
	velocity = sf::Vector2f((-sin(orientation)), (cos(orientation))) * maxSpeed;

	position = position + velocity;
	
}