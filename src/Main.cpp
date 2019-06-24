#include <vector>
#include <thread>
#include <string>

#include "Main.hpp"
#include "Map.h"
#include "Route.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Travelling Salesman Problem", sf::Style::Close, settings);

	const int townCount = 6;

	Map map(townCount, window);
	Route route(map, sf::Color(165, 165, 165));
	Route bestRoute(map, sf::Color(152, 209, 144, 150));

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

	bool b = true;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 0.5f)
		{
			clock.restart();
			if(b)
				b = !route.nextLexicOrder();
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
		if(b)
			route.drawRoads(window);
		else
			bestRoute.drawRoads(window);
		map.drawMap(window);
		window.draw(text);

		window.display();
	}

	return 0;
}
