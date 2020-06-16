#include "BoostManager.h"
#include <memory>



BoostManager::BoostManager()
{
	this->rand_time = sf::seconds((rand() % 10) + 5.f);
	pos1_1 = false; 
	pos1_2 = false; 
	pos2_1 = false; 
	pos2_2 = false;
	vec1_1 = sf::Vector2f(327, 327);
	vec1_2 = sf::Vector2f(903, 327);
	vec2_1 = sf::Vector2f(327, 903);
	vec2_2 = sf::Vector2f(903, 903);
}


BoostManager::~BoostManager()
{
}

void BoostManager::setTextures(const sf::Texture& txt_hp, const sf::Texture& txt_ms)
{
	textures.emplace(std::pair<BoostType::Type, sf::Texture>(BoostType::MS, txt_ms));
	textures.emplace(std::pair<BoostType::Type, sf::Texture>(BoostType::HP, txt_hp));
}

void BoostManager::spawn()
{
	sf::Vector2f pos = calculateSpawnPos();
	int i = (rand() % 2) + 1;

	boosts.emplace_back(Boost(pos, textures.find(BoostType::Type(i))->first, textures.find(BoostType::Type(i))->second));
	boost_time.restart();
}

void BoostManager::resetBoostTime()
{
	this->boost_time.restart();
}

bool BoostManager::canSpawn()
{
	if (boosts.size() < 4)
	{
		if (boost_time.getElapsedTime() > rand_time)
			return true;
	}
	else return false;
	return false;
}

int BoostManager::checkCollisionType(sf::FloatRect character)
{
	for (auto i = boosts.begin(); i != boosts.end(); i++)
	{
		if ((*i).checkCollide(character))
		{
			int type = (*i).getType();
			sf::Vector2f b_pos = (*i).getPosition();
			if (b_pos == vec1_1)
				pos1_1 = false;
			if (b_pos == vec1_2)
				pos1_2 = false;
			if (b_pos == vec2_1)
				pos2_1 = false;
			if (b_pos == vec2_2)
				pos2_2 = false;

			boosts.erase(i);

			resetBoostTime();
			return type;
		}
	}
	return 0;
}

void BoostManager::renderBoosts(std::shared_ptr<sf::RenderWindow> target)
{
	for (int i = 0; i != boosts.size(); i++)
	{
		boosts[i].render(target);
	}
}

sf::Vector2f BoostManager::calculateSpawnPos()
{

	while (true)
	{
		switch (int i = rand() % 4)
		{
		case 0:
			if (!pos1_1)
			{
				pos1_1 = true;
				return vec1_1;
				break;
			}

		case 1:
			if (!pos1_2)
			{
				pos1_2 = true;
				return vec1_2;
				break;
			}

		case 2:
			if (!pos2_1)
			{
				pos2_1 = true;
				return vec2_1;
				break;
			}

		case 3:
			if (!pos2_2)
			{
				pos2_2 = true;
				return vec2_2;
				break;
			}
		}
	}
}
