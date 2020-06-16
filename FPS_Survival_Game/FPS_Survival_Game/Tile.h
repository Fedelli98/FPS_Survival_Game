#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Tile
{
public:
	Tile(float x, float y, float tile_size_f, const sf::Texture& txt, int t_type);

	virtual ~Tile();

	sf::RectangleShape shape;
	bool walkable = true;
	void render(std::shared_ptr<sf::RenderTarget> target);

};

