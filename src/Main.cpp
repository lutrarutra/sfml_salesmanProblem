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

void updateVec(std::vector<Town *> &vec, int *orderArr)
{
	for (unsigned int i = 0; i < vec.size() - 1; ++i)
	{
		vec.at(orderArr[i])->disconnect();
		vec.at(orderArr[i])->connect(vec.at(orderArr[i + 1]));
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
	int *order = new int[townCount];
	int *bestOrder = new int[townCount];
	int distance = INT_MAX;
	int bestDistance = INT_MAX;

	srand(time(NULL));

	for (int i = 0; i < townCount; ++i)
	{
		towns.push_back(new Town(randomNum(10, window.getSize().x - 10), randomNum(10, window.getSize().y - 10), i));
		order[i] = i;
	}
	shuffle(order, townCount);
	updateVec(towns, order);

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
			updateVec(towns, order);
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
		}
		window.draw(text);

		window.display();
	}

	for (int i = 0; i < townCount; ++i)
	{
		delete towns.at(i);
	}

	delete[] bestOrder;
	delete[] order;

	return 0;
}
