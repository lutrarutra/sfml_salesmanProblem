#include <vector>
#include <stdlib.h>
#include <string>

#include "Main.hpp"
#include "Town.h"
#include "Road.h"

float calcDistance(std::vector<Town *> &vec)
{
	float d = 0;
	for (unsigned int i = 0; i < vec.size() - 1; ++i)
	{
		d += vec.at(i)->distance(vec.at(i + 1));
	}
	return d;
}

void updateVec(std::vector<Road *> &roads, std::vector<Town *> &towns, int *orderArr)
{
	for (unsigned int i = 0; i < roads.size(); ++i)
	{
		delete roads.at(i);
		roads[i] = new Road(towns.at(orderArr[i]), towns.at(orderArr[i+1]));
	}
}

void swap(int *arr, unsigned int i, unsigned int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

//This shuffle function keeps first town always at the first town
void shuffle(int *arr, unsigned int arraySize)
{
	srand(time(NULL));
	for (int i = arraySize - 1; i > 1; --i)
	{
		int j = rand() % i + 1;
		swap(arr, i, j);
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

	const int townCount = 8;
	std::vector<Town *> towns;
	std::vector<Road *> roads;
	int *order = new int[townCount];
	int *bestOrder = new int[townCount];
	int distance = INT_MAX;
	int bestDistance = INT_MAX;

	srand(time(NULL));

	for (int i = 0; i < townCount; ++i)
	{
		towns.push_back(new Town(randomNum(10, window.getSize().x - 10), randomNum(10, window.getSize().y - 10), i));
		if (i > 0)
			roads.push_back(new Road(towns.at(i - 1), towns.at(i)));
		order[i] = i;
	}
	shuffle(order, townCount);
	updateVec(roads, towns, order);

	sf::Clock clock;
	sf::Font font;
	sf::Event event;

	if (!font.loadFromFile("Roboto-Regular.ttf"))
	{
		return 1;
	}

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Black);
	int d = floor(calcDistance(towns));
	text.setString(std::to_string(d));

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
			shuffle(order, townCount);
			updateVec(roads, towns, order);
			distance = floor(calcDistance(towns));
			if (distance < bestDistance)
			{
				bestDistance = distance;
				memcpy(bestOrder, order, townCount * sizeof(int));
			}
			text.setString(std::to_string(d));
		}

		window.clear(sf::Color::White);
		for (int i = 0; i < townCount; ++i)
		{
			towns.at(i)->draw(window);
			if (i > 0)
				roads.at(i - 1)->draw(window);
		}
		window.draw(text);

		window.display();
	}

	for (int i = 0; i < townCount; ++i)
	{
		delete towns.at(i);
		if (i > 0)
			delete roads.at(i - 1);
	}

	delete[] bestOrder;
	delete[] order;

	return 0;
}
