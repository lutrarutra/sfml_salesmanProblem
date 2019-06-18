#include <vector>
#include <stdlib.h>
#include "Main.hpp"
#include "Town.h"

int randomNum(int min, int max)
{
	return min + ( std::rand() % ( max - min + 1 ) );
}

int main()
{
	int townCount = 50;
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Travelling Salesman Problem", sf::Style::Close, settings);

	std::vector<Town *> towns;
	srand(time(NULL));

	for (int i = 0; i < townCount; ++i)
	{
		towns.push_back(new Town(randomNum(10, window.getSize().x - 10),randomNum(10, window.getSize().y - 10), i));
	}


	sf::Clock clock;

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 1)
		{
			clock.restart();
		}

		window.clear(sf::Color::White);
		for (int i = 0; i < townCount; ++i)
		{
			towns.at(i)->draw(window);
		}
		window.display();
	}

	for (int i = 0; i < townCount; ++i)
	{
		delete towns.at(i);
	}

	return 0;
}
