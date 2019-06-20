#include <vector>
#include <string>

#include "Main.hpp"
#include "Map.h"
#include "Route.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Travelling Salesman Problem", sf::Style::Close, settings);

	const int townCount = 8;

	Map map(townCount, window);
	Route route(map);

	int distance = INT_MAX;
	int bestDistance = INT_MAX;

	srand(time(NULL));

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
	distance = floor(route.calcDistance());
	text.setString(std::to_string(distance));

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
			route.shuffle();
			route.updateRoads();
			distance = floor(route.calcDistance());
			if (distance < bestDistance)
			{
				bestDistance = distance;
			}
			text.setString(std::to_string(distance));
		}

		window.clear(sf::Color::White);
		route.drawRoads(window);
		map.drawMap(window);
		window.draw(text);

		window.display();
	}


	return 0;
}
