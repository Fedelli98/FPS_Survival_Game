#include "StRiflePlayerFight.h"

StRiflePlayerFight::StRiflePlayerFight()
{
	this->ratio = sf::seconds(1.f / 16.66667f);
	nrshot = 1;
}

void StRiflePlayerFight::shot(std::vector<std::shared_ptr<Bullet>>& bullets, BulletOwner::Owner owner,
	sf::Vector2f owner_pos, sf::Vector2f target_pos, const sf::Texture & texture)
{
	std::shared_ptr<Bullet>bullet(new Bullet(owner, owner_pos, texture));
	float dx = target_pos.x - owner_pos.x;
	float dy = target_pos.y - owner_pos.y;
	float lenght = sqrt(pow(dx, 2) + pow(dy, 2));
	sf::Vector2f normVect = sf::Vector2f(dx / lenght, dy / lenght);
	bullet->setDir(normVect);
	bullets.emplace_back(bullet);
}