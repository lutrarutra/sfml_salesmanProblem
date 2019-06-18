#include <vector>
#include <stdlib.h>
#include "Main.hpp"
#include "Town.h"

void swap(std::vector<Town *> &vec, int i, int j)
{
	Town *temp = vec.at(i);
	vec[i] = vec.at(j);
	vec[j] = temp;
}

void shuffle(std::vector<Town *> &vec)
{
	srand(time(NULL));
	for (int i = vec.size() - 1; i > 0; --i)
	{
		int j = rand() % i + 1;
		swap(vec, i, j);
	}
}

int randomNum(int min, int max)
{
	return min + (std::rand() % (max - min + 1));
}

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Travelling Salesman Problem", sf::Style::Close, settings);

	int townCount = 8;
	std::vector<Town *> towns;
	srand(time(NULL));

	for (int i = 0; i < townCount; ++i)
	{
		towns.push_back(new Town(randomNum(10, window.getSize().x - 10), randomNum(10, window.getSize().y - 10), i));
	}
	shuffle(towns);

	for (int i = 0; i < townCount - 1; ++i)
	{
		towns.at(i)->connect(towns.at(i + 1));
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
