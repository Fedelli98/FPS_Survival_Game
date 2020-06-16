#pragma once
#include "GridNode.h"
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <functional>
#include <utility>

class AStar
{
public:
	AStar(const GridNode& grid,const float max_d);
	AStar();

	virtual ~AStar();

	sf::Vector2f move(const sf::Time& deltatime, sf::Vector2f subject, sf::Vector2f target,
		std::list<sf::Vector2f> &movevect, float mov_speed);

	void setMaxDist(float m_distance);

	sf::Vector2f getTarget();
	void setTarget(sf::Vector2f trgt);

private:
	void a_star_search(const GridNode& graph, GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation>& came_from,
		std::unordered_map<GridLocation, double>& cost_so_far, std::list<sf::Vector2f> &movevect);

	    std::vector<GridLocation> reconstruct_path(GridLocation start, GridLocation goal,
		std::unordered_map<GridLocation, GridLocation> came_from);

protected:
	GridNode grid; 

	float max_distance;

	sf::Vector2f target;
	sf::Vector2f spostamento;
};




