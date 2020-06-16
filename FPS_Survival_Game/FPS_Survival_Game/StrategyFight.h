#pragma once
#include "SFML/Graphics.hpp"
#include "Bullet.h"
#include "Entity.h"

class Bullet;

class StrategyFight
{
public:
	StrategyFight() = default;
	virtual ~StrategyFight() = default;

	virtual void shot(std::vector<std::shared_ptr<Bullet>>& bullets, BulletOwner::Owner owner,
		sf::Vector2f owner_pos, sf::Vector2f target_pos, const sf::Texture & texture) = 0;
	virtual const sf::Time getRatio() { return ratio; };
	int nrshot = 0;

protected:
	sf::Time ratio;
};

