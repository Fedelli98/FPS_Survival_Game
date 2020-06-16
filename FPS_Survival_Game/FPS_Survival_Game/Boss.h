#pragma once
#include "Character.h"
#include "Astar.h"

class Boss :
	public Character
{
public:
	Boss(const GridNode& grid,const sf::Texture& texture);
	Boss();

	virtual ~Boss();

	void updateMove(const sf::Time& delta_time, sf::Vector2f target, float grid_size);
	bool shooting(const sf::Time& delta_time, sf::Vector2f target);
	void updateRotate(const sf::Vector2f target);
	void updateReload(const sf::Time& delta_time);
	void updateHud();

private:
	bool isInRange(sf::Vector2f obj1, sf::Vector2f obj2);

	void initVar();
	void initSprite(const GridNode& grid,const sf::Texture& texture);
	void initHitBox();

	const float max_distance = 64; //check tile
	const float range = 300;
	std::list <sf::Vector2f> move_vect;
	sf::Vector2f spostamento;

	AStar _m;
};

