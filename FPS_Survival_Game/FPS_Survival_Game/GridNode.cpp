#include "GridNode.h"

GridNode::GridNode(int width, int height) : width(width), height(height)
{
	DIRS = { GridLocation{1, 0}, GridLocation{0, -1}, GridLocation{-1, 0}, GridLocation{0, 1} };
}

GridNode::GridNode() : width(20), height(20)
{
}

void GridNode::initGrid(std::vector<GridLocation> obstacles)
{
	this->grid.resize(this->height, std::vector<GridLocation>());
	int k = 0;
	for (unsigned int i = 0; i < grid.size(); i++)
	{
		this->grid[i].resize(this->width);
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			GridLocation node;
			node.x = j;
			node.y = i;
			if (obstacles[k].x == j && obstacles[k].y == i)
			{
				node.walkable = false;
				k++;
			}
			else node.walkable = true;
			this->grid[i][j] = node;
		}
	}
}

const std::vector<std::vector<GridLocation>> GridNode::getGrid() const
{
	return this->grid;
}

const std::vector<GridLocation> GridNode::neighbors(const GridLocation& id) const
{
	std::vector<GridLocation> results;

	for (GridLocation dir : DIRS) {
		if (this->grid[id.y][id.x].walkable)
		{
			GridLocation next{ id.x + dir.x, id.y + dir.y };
			if (in_bounds(next))
			{
				results.push_back(next);
			}
		}
	}
	return results;
}

const int GridNode::cost(const GridLocation& start, const GridLocation& goal) const
{
	return abs(start.x - goal.x) + abs(start.y - goal.y);
}

bool GridNode::in_bounds(const GridLocation& id) const
{
	return 0 <= id.x && id.x < width
		&& 0 <= id.y && id.y < height;
}

