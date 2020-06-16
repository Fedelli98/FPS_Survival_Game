#include "AStar.h"

inline double heuristic(GridLocation a, GridLocation b) 
{
	return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}


AStar::AStar(const GridNode& grid, float max_d) : grid(grid)
{
	max_distance = max_d;
}

AStar::AStar()
{
}

AStar::~AStar()
{
}

sf::Vector2f AStar::move(const sf::Time& deltatime, sf::Vector2f subject, sf::Vector2f target,
	std::list<sf::Vector2f> &movevect, float mov_speed)
{
	sf::Vector2i mv; 
	if (max_distance == 64 && this->target != target)
	{
		if (!movevect.empty())
			movevect.clear();
		std::unordered_map<GridLocation, GridLocation> came_from;
		std::unordered_map<GridLocation, double> cost_so_far;
		GridLocation start = { static_cast<int>(subject.x / 64) , static_cast<int>(subject.y / 64) };
		GridLocation goal = { static_cast<int>(target.x / 64) , static_cast<int>(target.y / 64) };

		if (grid.getGrid()[goal.y][goal.x].walkable)
			a_star_search(this->grid, start, goal, came_from, cost_so_far, movevect);
		else return sf::Vector2f(0, 0);
		this->target = target;
	}

	if (!movevect.empty())
	{
		mv = sf::Vector2i(movevect.front());
		spostamento = static_cast <sf::Vector2f> (mv) * mov_speed * deltatime.asSeconds();
		float distance = sqrt(pow(spostamento.x, 2) + pow(spostamento.y, 2));
		max_distance -= distance;

		if (max_distance <= 0)
		{
			max_distance += distance;
			if (mv.x == 1)
			{
				spostamento.x = max_distance;
				spostamento.y = 0;
			}
			else if (mv.y == 1)
			{
				spostamento.y = max_distance;
				spostamento.x = 0;
			}
			else if (mv.x == -1)
			{
				spostamento.x = -max_distance;
				spostamento.y = 0;
			}
			else if (mv.y == -1)
			{
				spostamento.y = -max_distance;
				spostamento.x = 0;
			}
			max_distance = 64;
		}

		if (max_distance == 64)
		{
			movevect.pop_front();
		}
	}
	return spostamento;
}

void AStar::setMaxDist(float m_distance)
{
	this->max_distance = m_distance;
}

void AStar::setTarget(sf::Vector2f trgt)
{
	this->target = trgt;
}

sf::Vector2f AStar::getTarget()
{
	return target;
}

void AStar::a_star_search(const GridNode& graph, GridLocation start, GridLocation goal, std::unordered_map<GridLocation, GridLocation>& came_from, std::unordered_map<GridLocation, double>& cost_so_far, std::list<sf::Vector2f>& movevect)
{
	PriorityQueue<GridLocation, double> frontier;
	frontier.put(start, 0);

	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		GridLocation current = frontier.get();

		if (current == goal)
		{
			break;
		}

		for (GridLocation next : graph.neighbors(current))
		{
			double new_cost = cost_so_far[current] + graph.cost(current, next);
			if (cost_so_far.find(next) == cost_so_far.end()
				|| new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(next, goal);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}

	std::vector<GridLocation> path = reconstruct_path(start, goal, came_from);

	for (unsigned int i = 0; i < path.size() - 1; i++)
	{
		sf::Vector2f move = sf::Vector2f(static_cast<float>(path[i].x - path[i + 1].x),
			static_cast<float>(path[i].y - path[i + 1].y));
		movevect.push_back(-move);
	}
}

std::vector<GridLocation> AStar::reconstruct_path(GridLocation start, GridLocation goal, std::unordered_map<GridLocation, GridLocation> came_from)
{

	std::vector<GridLocation> path;
	GridLocation current = goal;

	while (current != start) 
	{
		path.push_back(current);
		current = came_from[current];
	}

	path.push_back(start);
	std::reverse(path.begin(), path.end());
	return path;
}

