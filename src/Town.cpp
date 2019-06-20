#include <math.h>

#include "Town.h"

Town::Town(int x, int y, int index)
{
	this->x = x;
	this->y = y;
	this->index = index;
	this->circle = new sf::CircleShape(8);
	if (index == 0)
		circle->setFillColor(sf::Color(144, 204, 136));
	else
		circle->setFillColor(sf::Color(68, 68, 68));

	circle->setOrigin(8, 8);
	circle->setPosition(x, y);
}

void Town::draw(sf::RenderWindow &window)
{
	window.draw(sf::CircleShape(*circle));
}

float Town::distance(Town *t)
{
	return sqrt(pow(this->x - t->x, 2) + pow(this->y - t->y, 2));
}

int Town::getX()
{
	return x;
}
int Town::getY()
{
	return y;
}

Town::~Town()
{
	delete this->circle;
}