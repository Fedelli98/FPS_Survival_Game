#pragma once
#include "Tile.h"
#include <fstream>
#include <sstream>
#include "GridNode.h"

class TileMap
{
public:
	explicit TileMap(sf::Vector2i map_size);
	virtual ~TileMap();

private:
	float grid_size_f;
	sf::Vector2i max_size;

    std::vector<std::vector<Tile*>> map;
	sf::Texture tileset;
		
	void loadFromFile(std::string file_name);

public:

	void render(std::shared_ptr<sf::RenderTarget> target);

	std::vector<sf::FloatRect> findWalls(int x, int y);

	std::vector<GridLocation> getObstacle();
	
	float getGridSize();

	sf::Vector2f const getSize();
};

