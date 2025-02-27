#include "Alien.h"
#include <math.h>

alien::alien(int type,float setSpeed)
{

	//direction = 3;

	if (type == 1)
	{
		CharTexture.loadFromFile("alien.png");
		Char.setTexture(CharTexture);
		Char.setOrigin(25, 42);
		timeToTarget = 10;
		position.x = 100;
		position.y = 100;
		maxSpeed = setSpeed;
	}

	if (type == 2)
	{
		CharTexture.loadFromFile("alien2.png");
		Char.setTexture(CharTexture);
		Char.setOrigin(25, 28);
		timeToTarget = 10;
		position.x = 800;
		position.y = 100;
		maxSpeed = setSpeed;
	}

	if (type == 3)
	{
		CharTexture.loadFromFile("alien3.png");
		Char.setTexture(CharTexture);
		Char.setOrigin(25, 22);
		timeToTarget = 10;
		position.x = 100;
		position.y = 800;
		maxSpeed = setSpeed;
	}

	if (type == 4)
	{
		CharTexture.loadFromFile("alien4.png");
		Char.setTexture(CharTexture);
		Char.setOrigin(25, 25);
		timeToTarget = 10;
		position.x = 800;
		position.y = 800;
		maxSpeed = setSpeed;
	}

	if (type == 5)
	{
		CharTexture.loadFromFile("alien5.png");
		Char.setTexture(CharTexture);
		Char.setOrigin(25, 25);
		timeToTarget = 10;
		position.x = 300;
		position.y = 300;
		maxSpeed = setSpeed;
	}


}

alien::~alien()
{
}

void alien::move()
{

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

void alien::seek(sf::Vector2f target)
{

	velocity = target - position;
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


void alien::wander(sf::Vector2f target)
{	
	seek(target);

	//wanderOrientation += (rand() % 5 - 1) * wanderRate;
	//targetOrientation = wanderOrientation + orientation;
	//sf::Vector2f targets = position + wanderOffset * orientation;
	//targets += wanderRadius * targetOrientation;


	//float wanderAngle = orientation + maxRotation * (rand() % 1 - 1);


	float temp;
	velocity = target - position;
	temp = getMag(velocity);
	velocity = velocity / temp;
	orientation = getOrientation();
	orientation = orientation * 180 / 3.14;
	orientation +=  maxRotation * (rand() % 3);


	//	//orientation += wanderAngle;

	velocity += sf::Vector2f((sinf(orientation)), (cosf(orientation))) * maxSpeed;
	//timer = 0;


	
}

void alien::arrive(sf::Vector2f target)
{
	velocity = target - position;

	float temp;
	temp = getMag(velocity);
	if (temp < radius)
	{
		return;
	}
	else
	{
		velocity = velocity / timeToTarget;

		float temp2 = getMag(velocity);
		if (temp2 > maxSpeed)
		{
			velocity = velocity / temp2;
			velocity = velocity * maxSpeed;
			orientation = getOrientation();
			orientation = orientation * 180 / 3.14;
		}
	}

	position = position + velocity;
}

void alien::pursue(sf::Vector2f target,sf::Vector2f targetVelocity)
{

	float timePrediction;
	sf::Vector2f futurePosition;
	velocity = target - position;
	float distance = sqrt(velocity.x*velocity.x + velocity.y*velocity.y);
	if (speed <= distance / maxTimePrediction) 
	{
		timePrediction = maxTimePrediction;
	}
	else 
	{
		timePrediction = distance / speed;
	}
	futurePosition = target + targetVelocity * timePrediction;
	seek(futurePosition);

}

void alien::collisionAvoidance()
{
	float temp;
	temp = getMag(velocity);
	
	//sf::Vector2f ahead = position + (velocity / temp) * MAX_SEE_AHEAD;
}