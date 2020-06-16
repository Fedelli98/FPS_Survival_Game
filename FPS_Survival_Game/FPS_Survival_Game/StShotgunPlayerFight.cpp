#include "StShotgunPlayerFight.h"

StShotgunPlayerFight::StShotgunPlayerFight()
{
	this->ratio = sf::seconds(1.f / 2.f);
	nrshot = 5;
}

void StShotgunPlayerFight::shot(std::vector<std::shared_ptr<Bullet>>& bullets, BulletOwner::Owner owner,
	sf::Vector2f owner_pos, sf::Vector2f target_pos, const sf::Texture & texture)
{
	float dir = 180.f / (nrshot * 360.f);
	int count = 0;
	if (nrshot % 2 == 0)
	{
		count = 1;
		for (int i = 0; i < nrshot; i++)
		{
			std::shared_ptr<Bullet>bullet(new Bullet(owner, owner_pos, texture));

			float dx = target_pos.x - owner_pos.x;
			float dy = target_pos.y - owner_pos.y;

			float lenght = sqrt(pow(dx, 2) + pow(dy, 2));
			sf::Vector2f normVect = sf::Vector2f(dx / lenght, dy / lenght);
			sf::Vector2f dir_p;
			if (i % 2 != 0)
			{
				dir_p = abs(normVect.x) < abs(normVect.y) ? sf::Vector2f(normVect.x + (dir * count), normVect.y) :
					sf::Vector2f(normVect.x, normVect.y + (dir * count));
				bullet->setDir(dir_p);
			}
			else
			{
				dir_p = abs(normVect.x) < abs(normVect.y) ? sf::Vector2f(normVect.x + (dir * -count), normVect.y) :
					sf::Vector2f(normVect.x, normVect.y + (dir * -count));
				bullet->setDir(dir_p);
			}
			if (i % 2 != 0 && i != 0)
				count++;
			bullets.emplace_back(bullet);
		}
	}
	else 
	{
		std::shared_ptr<Bullet> bullet(new Bullet(owner, owner_pos, texture));
		float dx = target_pos.x - owner_pos.x;
		float dy = target_pos.y - owner_pos.y;

		float lenght = sqrt(pow(dx, 2) + pow(dy, 2));
		sf::Vector2f normVect = sf::Vector2f(dx / lenght, dy / lenght);
		bullet->setDir(normVect);
		bullets.emplace_back(bullet);

		count = 1;
		for (int i = 0; i < nrshot - 1; i++)
		{
			std::shared_ptr<Bullet>bullet(new Bullet(owner, owner_pos, texture));

			float dx = target_pos.x - owner_pos.x;
			float dy = target_pos.y - owner_pos.y;

			float lenght = sqrt(pow(dx, 2) + pow(dy, 2));
			sf::Vector2f normVect = sf::Vector2f(dx / lenght, dy / lenght);
			sf::Vector2f dir_p;
			if (i % 2 != 0)
			{
				dir_p = abs(normVect.x) < abs(normVect.y) ? sf::Vector2f(normVect.x + (dir * count), normVect.y) :
					sf::Vector2f(normVect.x, normVect.y + (dir * count));
				bullet->setDir(dir_p);
			}
			else
			{
				dir_p = abs(normVect.x) < abs(normVect.y) ? sf::Vector2f(normVect.x + (dir * -count), normVect.y) :
					sf::Vector2f(normVect.x, normVect.y + (dir * -count));
				bullet->setDir(dir_p);
			}
			if (i % 2 != 0 && i != 0)
				count++;
			bullets.emplace_back(bullet);
		}
	}
}
