#include <SFML/Graphics.hpp>

class Town
{
public:
	Town(int x, int y, int index);
	~Town();
	void draw(sf::RenderWindow &window);
	void connect(Town *t);
	void disconnect();
	float distance(Town *t);

private:
	float PI = 3.14159265f;
	int x, y, index;
	sf::CircleShape *circle;
	sf::RectangleShape *road;
	Town *connectedTown;
};