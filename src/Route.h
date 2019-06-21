#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Map.h"
#include "Road.h"

class Route
{
public:
	Route(Map &map, sf::Color color);
	void copyOrder(Route* dest);
	void swap(int i, int j);
	void drawRoads(sf::RenderWindow &window);
	void shuffle();
	void updateRoads();
	void setColor(sf::Color &color);
	~Route();
	float calcDistance();

private:
	sf::Color color;
	unsigned int townCount;
	std::vector<Road *> roads;
	int *order;
	Map *map;
};