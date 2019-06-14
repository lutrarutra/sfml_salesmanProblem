#include <SFML/Graphics.hpp>

class Town
{
public:
	Town(int x, int y, int index);
	void connect(Town *t);
	~Town();
	void draw(sf::RenderWindow &window);

private:
	int x, y, index;
	sf::CircleShape *circle;
	sf::RectangleShape *road;
	Town *connectedTown;
};