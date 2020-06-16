#include "CollisionManager.h"
#include <iostream>
#include "Collision.h"


CollisionManager::CollisionManager()
{
	this->collide = false;
}


CollisionManager::~CollisionManager()
{
}

sf::Vector2f CollisionManager::CollideWithWalls(const sf::FloatRect & rectSp1, const std::vector<sf::FloatRect> walls)
{
	sf::Vector2f dir(0, 0);

	for (int i = 0; i != walls.size(); i++)
	{
		if (sat_test(rectSp1, walls[i]))
		{
			this->collide = true;
			if(out_mtv.x == 0 || out_mtv.y == 0)
			{
				dir += out_mtv;
			}
		}
	}
	if (dir.x == 0 && dir.y == 0)
	{
		this->collide = false;
		out_mtv = sf::Vector2f(0, 0);
		return
			sf::Vector2f(0, 0);
	}
	else
		return dir;
}

sf::Vector2f CollisionManager::CollideWithEntity(const sf::FloatRect & rect_sp1, const sf::FloatRect & rect_sp2)
{
	if (rect_sp1 != rect_sp2)
	{
		if (sat_test(rect_sp1, rect_sp2))
		{
			collide = true;
			return out_mtv;
		}
		collide = false;
		return out_mtv = sf::Vector2f(0.f, 0.f);
	}
	else 
		return out_mtv = sf::Vector2f(0.f, 0.f);
}

void CollisionManager::reset()
{
	this->out_mtv = sf::Vector2f(0.f, 0.f);
	this->collide = false;
}

void CollisionManager::resetOutMtv()
{
	this->out_mtv = sf::Vector2f(0.f, 0.f);
}

void CollisionManager::resetCollide()
{
	this->collide = false;
}

bool CollisionManager::isCollide()
{
	return
		this->collide;
}


sf::Vector2f CollisionManager::getOutMtv()
{
	return
		this->out_mtv;
}

bool CollisionManager::sat_test(const sf::FloatRect & rect_sp1, const sf::FloatRect & rect_sp2)
{
	float proj_x, proj_y, overlap_x, overlap_y;

	proj_x = std::max(rect_sp1.left + rect_sp1.width, rect_sp2.left + rect_sp2.width) - std::min(rect_sp1.left, rect_sp2.left);
	if (proj_x < rect_sp1.width + rect_sp2.width) {
		{
			overlap_x = rect_sp1.width + rect_sp2.width - proj_x;
		}
		proj_y = std::max(rect_sp1.top + rect_sp1.height, rect_sp2.top + rect_sp2.height) - std::min(rect_sp1.top, rect_sp2.top);
		if (proj_y < rect_sp1.height + rect_sp2.height) {
			{
				overlap_y = rect_sp1.height + rect_sp2.height - proj_y;
				out_mtv.x = out_mtv.y = 0;

				if (overlap_x < overlap_y) {
					out_mtv.x = overlap_x * (rect_sp1.left < rect_sp2.left ? -1 : 1);
				}
				else {
					out_mtv.y = overlap_y * (rect_sp1.top < rect_sp2.top ? -1 : 1);
				}
			}
			return true;
		}
	}
	return false;
}
