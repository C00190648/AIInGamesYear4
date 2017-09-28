#include "Alien.h"

Character::Character(int type)
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
	}
}

Character::~Character()
{
}

void Character::move()
{
	if (direction == RIGHT)
	{
		position.x += speed;

		if (position.x > 1000)
		{
			position.x = 5;
		}
	}
	else if (direction == LEFT)
	{
		position.x -= speed;


		if (position.x < -50)
		{
			position.x = 990;
		}
	}

	else if (direction == DOWN)
	{
		position.y += speed;

		if (position.y > 1000)
		{
			position.y = 5;
		}
	}

	else if (direction == UP)
	{
		position.y -= speed;

		if (position.y < -50)
		{
			position.y = 990;
		}
	}
}

void Character::changeVelocity()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed)
	{
		speed += 0.01;
		pressed = true;

		if (speed > 15)
		{
			speed = 15;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed)
	{
		speed -= 0.01;
		pressed = true;

		if (speed < 0)
		{
			speed = 0;
		}

	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pressed = false;
	}
}

void Character::draw(sf::RenderWindow& window)
{
	Char.setPosition(position.x, position.y);
	window.draw(Char);
}