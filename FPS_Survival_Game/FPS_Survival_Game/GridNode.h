#pragma once
#include <queue>
#include <unordered_map>
#include <array>
#include <iostream>

struct GridLocation
{
	int x, y;
	bool walkable = true;

	inline bool operator==(const GridLocation& second) const
	{
		return (this->x == second.x && this->y == second.y);
	}

	inline bool operator!=(const GridLocation& second) const
	{
		return !operator==(second);
	}

	bool operator < (const GridLocation& b) const 
	{
		return std::tie(this->x, this->y) < std::tie(b.x, b.y);
	}

	inline bool operator>(const GridLocation& sc) const
	{
		return !operator<(sc);
	}
};

template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get()
	{
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};

namespace std {
	template <> struct hash<GridLocation> {
		typedef GridLocation argument_type;
		typedef std::size_t result_type;
		std::size_t operator()(const GridLocation& id) const {
			return std::hash<int>()(id.x ^ (id.y << 4));
		}
	};
}


class GridNode
{
public:
	GridNode(int width, int height);
	GridNode();

	virtual ~GridNode() {};

	void initGrid(std::vector<GridLocation> obstacles);

	const std::vector< std::vector<GridLocation> > getGrid()const;

	const std::vector<GridLocation> neighbors(const GridLocation& id)const;

	const int cost(const GridLocation& start, const GridLocation& goal)const;

private:

	std::vector< std::vector<GridLocation> > grid;

	std::array<GridLocation, 4> DIRS;

	const int width;
	const int height;

	bool in_bounds(const GridLocation& id) const;
	
};