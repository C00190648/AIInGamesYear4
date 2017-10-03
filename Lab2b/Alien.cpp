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
		speed = 2;

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
	float temp = getMag(velocity);
	velocity = velocity / temp;
	velocity = velocity * maxSpeed;
	orientation = getOrientation(orientation, velocity, target);
	orientation = (orientation * 180) / 3.14;
	Char.setRotation(orientation);
}



float alien::getOrientation(float orientation, sf::Vector2f velocity, Player target)
{
	float temp = getMag(velocity);
	if (temp > 0)
	{
		return atan2(-position.y ,position.x);
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
	orientation = getOrientation(orientation, velocity, target);
	//orientation = orientation + MaxRotation * random(-1, +1);
	//Velocity = (-sin(orientation), cos(orientation))*maxSpeed;
}