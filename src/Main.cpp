#include "Main.hpp"
#include "Town.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Travelling Salesman Problem", sf::Style::Close, settings);

	Town t1(window.getSize().x / 2, window.getSize().y / 2, 0);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear(sf::Color::White);
		t1.draw(window);
		window.display();
	}

	return 0;
}
