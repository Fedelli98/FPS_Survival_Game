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

	pos_in_texture = sf::Vector2u(static_cast<unsigned int>(j * tile_size_f), static_cast<unsigned int>(i * tile_size_f));
	this->shape.setTextureRect(sf::IntRect(pos_in_texture.x, pos_in_texture.y, 64, 64));
}


Tile::~Tile()
{
}


void Tile::render(std::shared_ptr<sf::RenderTarget> target)
{
  	target->draw(shape);
}
