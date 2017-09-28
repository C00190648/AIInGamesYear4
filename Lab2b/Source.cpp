#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <iostream>
#include "Alien.h"
#include "Player.h"

// create window for the game
sf::RenderWindow window(sf::VideoMode(1000, 1000), "Lab1"); //pick a size

int main()
{

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

		player.move();

		AI.move();

		player.changeVelocity();
		window.clear();
		AI.draw(window);
		player.draw(window);
		window.display();
	}

	return 0;

}