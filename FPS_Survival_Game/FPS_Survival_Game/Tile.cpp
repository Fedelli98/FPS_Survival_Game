 #include "Tile.h"

Tile::Tile(float x, float y, float tile_size_f, const sf::Texture& txt, int t_type)
{
	if(t_type == 9)
	{
		walkable = false;
		shape.setOutlineColor(sf::Color::Transparent);
	}

	this->shape.setSize(sf::Vector2f(tile_size_f, tile_size_f));
	this->shape.setPosition(x, y);

	this->shape.setTexture(&txt);
	sf::Vector2u pos_in_texture;
	
	//calculate the type of tile
	this->type_tile = t_type;
	int n = (txt.getSize().x / static_cast <unsigned>(tile_size_f));
	int i = 0;
	int j = t_type % n;

	while(t_type > n)
	{
		t_type -= (txt.getSize().x / static_cast <unsigned>(tile_size_f));
		i++;
	}

	if (i >= 1)
		j -= 1;
	
	if (j < 0)
	{
		i = -1;
		sf::Vector2i pos_in_texture2 = sf::Vector2i(static_cast<int>(j * tile_size_f), static_cast<int>(i * tile_size_f));
		this->shape.setTextureRect(sf::IntRect(pos_in_texture2.x, pos_in_texture2.y, 0, 0));
	}
	else
	{
		pos_in_texture = sf::Vector2u(static_cast<unsigned int>(j * tile_size_f), static_cast<unsigned int>(i * tile_size_f));
		this->shape.setTextureRect(sf::IntRect(pos_in_texture.x, pos_in_texture.y, 64, 64));
	}
}

Tile::Tile()
{
}


Tile::~Tile()
{
}


sf::RectangleShape * Tile::getShape()
{
	return &shape;
}

void Tile::calculateType(float x, float y, int tilewidth)
{
	this->type_tile = (x / tilewidth + (y * (this->shape.getSize().x / tilewidth)));
}

void Tile::setType(int type)
{
	this->type_tile = type;
}

int Tile::getType()
{
	return type_tile;
}

void Tile::render(std::shared_ptr<sf::RenderTarget> target)
{
  	target->draw(shape);
}
