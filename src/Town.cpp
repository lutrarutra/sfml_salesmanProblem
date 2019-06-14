#include "Town.h"
#include <math.h>


Town::Town(int x, int y, int index)
{
	this->connectedTown = nullptr;
	this->x = x;
	this->y = y;
	this->index = index;
	this->circle = new sf::CircleShape(5);
	circle->setFillColor(sf::Color::Black);
	circle->setOrigin(5, 5);
	circle->setPosition(x, y);
}

void Town::connect(Town *t)
{
	this->connectedTown = t;
	float angle = tanh(this->y - t->y / this->x - t->x);
	this->road = new sf::RectangleShape();
}

void Town::draw(sf::RenderWindow &window)
{
	window.draw(sf::CircleShape(*circle));
}

Town::~Town()
{
	delete this->circle;
	if(this->road != nullptr)
		delete this->road;
}