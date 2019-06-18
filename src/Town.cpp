#include <math.h>

#include "Town.h"

Town::Town(int x, int y, int index)
{
	this->connectedTown = nullptr;
	this->road = nullptr;
	this->x = x;
	this->y = y;
	this->index = index;
	this->circle = new sf::CircleShape(7);
	circle->setFillColor(sf::Color::Red);
	circle->setOrigin(5, 5);
	circle->setPosition(x, y);
}

void Town::disconnect()
{
	if (this->road != nullptr)
	{
		delete road;
		road = nullptr;
		this->connectedTown = nullptr;
	}
}

void Town::connect(Town *t)
{
	this->connectedTown = t;
	float angle = atan2((this->y - t->y), (this->x - t->x)) * 180 / PI - 180;
	this->road = new sf::RectangleShape(sf::Vector2f(distance(t), 4));
	this->road->setPosition(sf::Vector2f(x, y));
	this->road->setFillColor(sf::Color::Black);
	this->road->setOrigin(0, 0);
	this->road->setRotation(angle);
}

void Town::draw(sf::RenderWindow &window)
{
	window.draw(sf::CircleShape(*circle));
	if (road != nullptr)
		window.draw(sf::RectangleShape(*road));
}

float Town::distance(Town *t)
{
	return sqrt(pow(this->x - t->x, 2) + pow(this->y - t->y, 2));
}

Town::~Town()
{
	delete this->circle;
	if (this->road != nullptr)
		delete this->road;
}