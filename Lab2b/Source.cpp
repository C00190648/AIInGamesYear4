#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include "Alien.h"
#include "Player.h"

// create window for the game
sf::RenderWindow window(sf::VideoMode(1000, 1000), "Lab1"); //pick a size





int main()
{
	sf::Clock clock;

	const float FPS = 60.0f;
	const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	clock.restart();
	sf::Event event;
	alien AI(1);
	Player player;

	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}


		}

		timeSinceLastUpdate += clock.restart();
		//update every 60th of a second
		if (timeSinceLastUpdate > timePerFrame)
		{

			player.move();

			//AI.seek(player);
			AI.wander(player);
			//AI.move();
			player.changeVelocity();
			timeSinceLastUpdate = sf::Time::Zero;

		}
		window.clear(sf::Color(0, 0, 0, 0));
		AI.draw(window);
		player.draw(window);
		window.display();
	}

	return 0;

}