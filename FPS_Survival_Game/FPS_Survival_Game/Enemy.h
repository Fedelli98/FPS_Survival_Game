#pragma once
#include "Character.h"
#include "AStar.h"
#include "TileSheetAnimator.h"

class Enemy :
	public Character
{

public:
	Enemy(const sf::Texture& texture, const GridNode& grid, float grid_size);
	Enemy();
	virtual ~Enemy();

	AStar _m;

	void updateMove(const sf::Time& delta_time, sf::Vector2f target, float grid_size);
	void updateRotate(sf::Vector2f target);
	void updateSpriteAttack(const sf::Time& delta_time);
	bool canHit(const sf::Time& deltatime);
	void updateHud();

public:
	TileSheetAnimator animator;
	TileSheetAnimator shoot_animator;
private:
	void initVar();
	void initSprite(const GridNode& grid,const sf::Texture & texture);
	void initHitBox(float grid_size); 

	const float max_distance = 64; //check tile

	std::list <sf::Vector2f> move_vect;
};

