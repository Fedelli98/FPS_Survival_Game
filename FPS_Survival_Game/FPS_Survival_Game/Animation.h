#pragma once
#include "TileSheetAnimator.h"
#include "TextureHolder.h"

#include <SFML/Graphics.hpp>
class Animation : public TileSheetAnimator
{
public:
	Animation(const sf::Texture& texture, Textures::OBJECTS id, sf::Vector2f position, float timer,
		sf::Vector2u dim, sf::Vector2u imagecount, float switchtime, sf::Vector2f scale = sf::Vector2f(1, 1), sf::Vector2u startimage = sf::Vector2u(0, 0));
	~Animation();

	float getTimer();
	sf::RectangleShape getShape();
	Textures::OBJECTS getId();
	void setShapeTxtRect(sf::IntRect shape);

	void updateTimer(const sf::Time& delta_time);

	void render(std::shared_ptr<sf::RenderWindow> target);
private:
	float timer;
	sf::RectangleShape shape;
	sf::IntRect rect;
	Textures::OBJECTS id;

};

