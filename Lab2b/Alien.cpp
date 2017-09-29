#include "Alien.h"

alien::alien(int type)
{
	direction = rand() % 5 + 1;

	//direction = 3;

	if (type == 1)
	{
		CharTexture.loadFromFile("alien.png");
		Char.setTexture(CharTexture);

		position.x = 500;
		position.y = 500;
		speed = 0.03;

		rotation = Char.getRotation();
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
	window.draw(Char);
}

void alien::seek(Player target)
{
	velocity = target.position - position;
	velocity = velocity / getMag(velocity);
	velocity = velocity * maxSpeed;
	orientation = getOrientation(orientation, velocity);
	orientation = orientation * 180 / 3.14;
	Char.setRotation(orientation);
}



float alien::getOrientation(float orientation, sf::Vector2f velocity)
{
	float temp = getMag(velocity);
	if (temp > 0)
	{
		return atan2(-position.y ,position.x);
	}
	else
	{
		

	}
}

float alien::getMag(sf::Vector2f velocity)
{
	float temp = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
	return temp;
}