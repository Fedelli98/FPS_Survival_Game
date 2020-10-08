#include "TileMap.h"



TileMap::TileMap(sf::Vector2i map_size)
{
	this->grid_size_f = 64.f;
	this->max_size.x = map_size.x;
	this->max_size.y = map_size.y;

	if(!tileset.loadFromFile("Sources/tileSheet/tilesheet.png"))
	{//THROW
		throw std::runtime_error("il file errore");
	}
	tileset.loadFromFile("Sources/tileSheet/tilesheet.png");
	
	std::ifstream openfile("Sources/Mappa.txt");
		//devo leggere il file e in base al numero trovato mettere un tile diverso 
	if(openfile.is_open())
	{
		while (!openfile.eof())
		{
			this->map.resize(static_cast<unsigned int>(this->max_size.y), std::vector<Tile*> ());
			int y = 0;
			while (y < this->max_size.y)
			{
				int x = 0;
				while (x < this->max_size.x)
				{
					this->map[y].resize(static_cast<unsigned int>(this->max_size.x), NULL);

					std::string str, value;
					std::getline(openfile, str);
					std::stringstream stream(str);

					while (std::getline(stream, value, ' ') && openfile.peek() != '\n')
					{
						std::string t_type = value.substr(0, value.find(','));
						int tile_type = atoi(t_type.c_str());

						this->map[y][x] = new Tile(x * this->grid_size_f, y * grid_size_f, this->grid_size_f, tileset, tile_type);
						x++;
					}
				}
				y++;
			}

		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::loadFromFile(std::string file_name)
{
	std::ifstream openfile("Sources/Mappa.txt");
}


void TileMap::render(std::shared_ptr<sf::RenderTarget> target)
{
	for (auto &x : this->map)
	{
		for (auto &y : x)
		{
			y->render(target);
		}
	}
}

std::vector<sf::FloatRect> TileMap::findWalls(int x, int y)
{
	sf::Vector2i pos(static_cast<int>(x / grid_size_f), static_cast<int>(y / grid_size_f));
	std::vector<sf::FloatRect> wallvect;
	
	if (pos.y < 20 && pos.y >= 0)
	{
		if (pos.x < 20 && pos.x >= 0)
		{

			if (!map[pos.y][pos.x]->walkable)
				wallvect.push_back(map[pos.y][pos.x]->shape.getGlobalBounds());

			if (pos.y > 0)
			{
				if (!map[pos.y - 1][pos.x]->walkable)
					wallvect.push_back(map[pos.y - 1][pos.x]->shape.getGlobalBounds());
				if (pos.x < max_size.x - 1)
					if (!map[pos.y - 1][pos.x + 1]->walkable)
						wallvect.push_back(map[pos.y - 1][pos.x + 1]->shape.getGlobalBounds());
				if (pos.x > 0)
					if (!map[pos.y - 1][pos.x - 1]->walkable)
						wallvect.push_back(map[pos.y - 1][pos.x - 1]->shape.getGlobalBounds());
			}
			if (pos.y < max_size.y - 1)
			{
				if (!map[pos.y + 1][pos.x]->walkable)
					wallvect.push_back(map[pos.y + 1][pos.x]->shape.getGlobalBounds());
				if (pos.x < max_size.x - 1)
					if (!map[pos.y + 1][pos.x + 1]->walkable)
						wallvect.push_back(map[pos.y + 1][pos.x + 1]->shape.getGlobalBounds());
				if (pos.x > 0)
					if (!map[pos.y + 1][pos.x - 1]->walkable)
						wallvect.push_back(map[pos.y + 1][pos.x - 1]->shape.getGlobalBounds());
			}
			if (pos.x > 0)
			{
				if (!map[pos.y][pos.x - 1]->walkable)
					wallvect.push_back(map[pos.y][pos.x - 1]->shape.getGlobalBounds());
			}
			if (pos.x <= 20 && pos.x >=0)
			{
				if (pos.x < max_size.x - 1)
				{
					if (!map[pos.y][pos.x + 1]->walkable)
						wallvect.push_back(map[pos.y][pos.x + 1]->shape.getGlobalBounds());
				}
			}
		}
	}
	return wallvect;
}

std::vector<GridLocation> TileMap::getObstacle()
{
	std::vector<GridLocation> obstacles;

	for (int i = 0; i < max_size.y; i++)
	{
		for (int j = 0; j < max_size.x; j++)
		{
			if (!map[i][j]->walkable)
			{
				GridLocation node;
				node.walkable = false;
				node.x = j;
				node.y = i;
				obstacles.push_back(node);
			}
		}
	}
	return obstacles;
}

float TileMap::getGridSize()
{
	return this->grid_size_f;
}

sf::Vector2f const TileMap::getSize()
{
	return 
		sf::Vector2f(grid_size_f * max_size.x, grid_size_f * max_size.y);
}
