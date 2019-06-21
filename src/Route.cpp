#include <iostream>

#include "Route.h"

Route::Route(Map &map, sf::Color color)
{
	this->map = &map;
	this->townCount = map.getTownCount();
	this->order = new int[townCount];
	this->color = color;
	for (unsigned int i = 0; i < townCount; ++i)
	{
		order[i] = i;
	}
	roads.reserve(townCount - 1);
	for (unsigned int i = 0; i < townCount - 1; ++i)
	{
		roads.push_back(new Road(map.getTowns().at(order[i]), map.getTowns().at(order[i + 1]), color));
	}
}

void Route::copyOrder(Route *dest)
{
	for (unsigned int i = 0; i < townCount; ++i)
	{
		dest->order[i] = this->order[i];
	}
}

void Route::drawRoads(sf::RenderWindow &window)
{
	for (unsigned int i = 0; i < townCount - 1; ++i)
	{
		roads.at(i)->draw(window);
	}
}

void Route::updateRoads()
{
	for (unsigned int i = 0; i < townCount - 1; ++i)
	{
		delete roads.at(i);
		roads.at(i) = new Road(map->getTowns().at(order[i]), map->getTowns().at(order[i + 1]), this->color);
	}
}

void Route::swap(int i, int j)
{
	int temp = order[i];
	order[i] = order[j];
	order[j] = temp;
}

//This shuffle function keeps first town always at the first town
void Route::shuffle()
{
	srand(time(NULL));
	for (int i = townCount - 1; i > 1; --i)
	{
		int j = rand() % i + 1;
		swap(i, j);
	}
}

float Route::calcDistance()
{
	float d = 0;
	for (unsigned int i = 0; i < townCount - 1; ++i)
	{
		d += map->getTowns().at(order[i])->distance(map->getTowns().at(order[i + 1]));
	}
	return d;
}

Route::~Route()
{
	for (unsigned int i = 0; i < townCount - 1; ++i)
	{
		delete roads.at(i);
	}
}