#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Map.h"
#include "Road.h"

class Route
{
public:
	Route(Map &map);
	void swap(int i, int j);
	void drawRoads(sf::RenderWindow &window);
	void shuffle();
	void updateRoads();
	~Route();
	float calcDistance();

private:
	unsigned int townCount;
	std::vector<Road *> *roads;
	int *order;
	Map *map;
};