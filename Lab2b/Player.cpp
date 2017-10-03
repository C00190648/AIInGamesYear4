#include "Player.h"

Player::Player()
{
	//direction = rand() % 5 + 1;

	//direction = 3;



	playerTexture.loadFromFile("player.png");
	player.setTexture(playerTexture);

	//player.setOrigin(player.getGlobalBounds().width / 2.0f, player.getGlobalBounds().height / 2.0f);

	position.x = 600;
	position.y = 600;
	rotation = player.getRotation();
	speed = 3;

}

Player::~Player()
{
}

void Player::move()
{
	velocity.x = speed * cosf(rotation);
	velocity.y = speed * sinf(rotation);

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

void Player::changeVelocity()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !pressed)
	{
		speed += 1;
		pressed = true;

		if (speed > 15)
		{
			speed = 15;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !pressed)
	{
		speed -= 1;
		pressed = true;

		if (speed < 0)
		{
			speed = 0;
		}

	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotation -= 0.0872;
		player.setRotation(player.getRotation() - 5);

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{

		rotation += 0.0872;
		player.setRotation(player.getRotation() + 5);

	}

}

void Player::draw(sf::RenderWindow& window)
{
	player.setPosition(position);
	window.draw(player);
}