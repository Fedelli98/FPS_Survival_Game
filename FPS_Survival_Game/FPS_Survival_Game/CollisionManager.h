#pragma once

#include <SFML/Graphics.hpp>

class CollisionManager
{

public:
	CollisionManager();
	~CollisionManager();

	sf::Vector2f CollideWithWalls(const sf::FloatRect & rectSp1, const std::vector<sf::FloatRect> walls);
	sf::Vector2f CollideWithEntity(const sf::FloatRect & rectSp1, const sf::FloatRect & rectSp2);

	void reset();
	void resetOutMtv();
	void resetCollide();

	bool isCollide();

	sf::Vector2f getOutMtv();

private:
	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2);

	bool collide;
	sf::Vector2f out_mtv;
};
