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
	alien wanderAI(1, 3);
	alien seekAI(2, 6.5);
	alien arriveAI1(3, 10);
	alien arriveAI2(4, 7);
	alien pursueAI(5, 4);
	
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
			wanderAI.wander(player.position);
			seekAI.seek(player.position);
			arriveAI1.arrive(player.position);
			arriveAI2.arrive(player.position);
			pursueAI.pursue(player.position, player.velocity);

			wanderAI.move();
			seekAI.move();
			arriveAI1.move();
			arriveAI2.move();
			pursueAI.move();
			player.changeVelocity();
			timeSinceLastUpdate = sf::Time::Zero;

		}
		window.clear();

		wanderAI.draw(window);
		seekAI.draw(window);
		arriveAI1.draw(window);
		arriveAI2.draw(window);
		pursueAI.draw(window);

		player.draw(window);
		window.display();
	}

	return 0;

}

