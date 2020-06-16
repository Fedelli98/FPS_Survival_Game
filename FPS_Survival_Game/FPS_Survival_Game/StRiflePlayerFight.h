#pragma once
#include "StrategyFight.h"

class StRiflePlayerFight :
	public StrategyFight
{
public:
	StRiflePlayerFight();
	virtual ~StRiflePlayerFight() = default;

	virtual void shot(std::vector<std::shared_ptr<Bullet>>& bullets, BulletOwner::Owner owner,
		sf::Vector2f owner_pos, sf::Vector2f target_pos, const sf::Texture & texture);
};

