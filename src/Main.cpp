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
	Route route(map, sf::Color(165, 165, 165));
	Route bestRoute(map, sf::Color(152, 209, 144));

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
	int distance = floor(route.calcDistance());
	text.setString(std::to_string(distance));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 1)
		{
			clock.restart();
			route.shuffle();
			route.updateRoads();
			distance = floor(route.calcDistance());
			if (distance < bestDistance)
			{
				bestDistance = distance;
				route.copyOrder(&bestRoute);
				bestRoute.updateRoads();
			}
			text.setString("Distance: " + std::to_string(distance) + " Best distance: " + std::to_string(bestDistance));
		}

		window.clear(sf::Color::White);
		route.drawRoads(window);
		bestRoute.drawRoads(window);
		map.drawMap(window);
		window.draw(text);

		window.display();
	}


	return 0;
}
