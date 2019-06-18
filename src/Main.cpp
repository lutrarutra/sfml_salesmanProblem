#include <vector>
#include <stdlib.h>
#include <string>

#include "Main.hpp"
#include "Town.h"

float calcDistance(std::vector<Town *> &vec)
{
	float d = 0;
	for (unsigned int i = 0; i < vec.size() - 1; ++i)
	{
		d += vec.at(i)->distance(vec.at(i + 1));
	}
	return d;
}

void updateVec(std::vector<Town *> &vec)
{
	for (unsigned int i = 0; i < vec.size() - 1; ++i)
	{
		vec.at(i)->disconnect();
		vec.at(i)->connect(vec.at(i + 1));
	}
}

void swap(std::vector<Town *> &vec, unsigned int i, unsigned int j)
{
	Town *temp = vec.at(i);
	vec[i] = vec.at(j);
	vec[j] = temp;
}

//This shuffle function keeps first town always as same first town
void shuffle(std::vector<Town *> &vec)
{
	srand(time(NULL));
	for (int i = vec.size() - 1; i > 1; --i)
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
	updateVec(towns);

	sf::Clock clock;
	sf::Font font;
	sf::Event event;

	if (!font.loadFromFile("Roboto-Regular.ttf"))
	{
		return 1;
	}

	sf::Text text;
	text.setFont(font);

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 3)
		{
			clock.restart();
			shuffle(towns);
			updateVec(towns);
			text.setString(std::to_string(floor(calcDistance(towns))));
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::Black);
		}

		window.clear(sf::Color::White);
		for (int i = 0; i < townCount; ++i)
		{
			towns.at(i)->draw(window);
		}
		window.draw(text);

		window.display();
	}

	for (int i = 0; i < townCount; ++i)
	{
		delete towns.at(i);
	}

	return 0;
}
