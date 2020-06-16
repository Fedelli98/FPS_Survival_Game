#include "Boost.h"

Boost::Boost(sf::Vector2f spawn_pos, BoostType::Type type, const sf::Texture & texture)
{
	switch (type)
	{
	case 1: // 1 = HP
		this->b_type = type;
		initHp(spawn_pos, texture);
		break;

	case 2: // 2 = MS
		this->b_type = type;
		initMs(spawn_pos, texture);
		break;
	}
}

Boost::~Boost()
{
}

bool Boost::checkCollide(const sf::FloatRect& character)
{
	return(sat_test(character, getHitBox().getGlobalBounds(), NULL));
}

BoostType::Type Boost::getType()
{
	return
		this->b_type;
}

void Boost::initHp(sf::Vector2f spawn_pos, const sf::Texture & texture)
{
	initSpriteHp(spawn_pos, texture);
	initHitBoxHp();
}

void Boost::initMs(sf::Vector2f spawn_pos, const sf::Texture & texture)
{
	initSpriteMs(spawn_pos, texture);
	initHitBoxMs();
}

void Boost::initSpriteHp(sf::Vector2f spawn_pos, const sf::Texture & texture)
{ 
	sprite.setTexture(texture);	   //TEXTURE
	sprite.setScale(0.1f, 0.1f);   //SCALE
	sprite.setPosition(spawn_pos); //POS
	sprite.setOrigin(0, 0);        //ORIGIN
}

void Boost::initHitBoxHp()
{
	hit_box.setSize(sf::Vector2f(512 , 512));        //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(0, 0);                         //ORIGIN
}

void Boost::initSpriteMs(sf::Vector2f spawn_pos, const sf::Texture & texture)
{
	sprite.setTexture(texture);	   //TEXTURE
	sprite.setScale(0.05f, 0.05f); //SCALE
	sprite.setPosition(spawn_pos); //POS
	sprite.setOrigin(0, 0);        //ORIGIN
}

void Boost::initHitBoxMs()
{
	hit_box.setSize(sf::Vector2f(1200, 1200));        //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent);  //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());             //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(0, 0);                         //ORIGIN
}
