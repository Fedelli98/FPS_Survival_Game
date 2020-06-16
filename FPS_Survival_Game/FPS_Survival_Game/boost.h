#pragma once
#include "Character.h"
#include <ctime>

namespace BoostType
{
	enum Type {HP = 1, MS = 2 };
};


class Boost :
	public Entity
{
public:
	Boost() {};
	Boost(sf::Vector2f spawn_pos, BoostType::Type type, const sf::Texture & texture);
	virtual ~Boost();

	bool checkCollide(const sf::FloatRect& character);

	BoostType::Type getType();

private:
	void initHp(sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initMs(sf::Vector2f spawn_pos, const sf::Texture & texture);

	void initSpriteHp(sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initHitBoxHp();

	void initSpriteMs(sf::Vector2f spawn_pos, const sf::Texture & texture);
	void initHitBoxMs();

	BoostType::Type b_type;
};

