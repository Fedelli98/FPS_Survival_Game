#include "Pet.h"



Pet::Pet(const sf::Texture & texture, sf::Vector2f spawn_pos)
{
	initVar();
	initSprite(texture, spawn_pos);
	initHitbox();
}

Pet::Pet()
{
}


Pet::~Pet()
{
}

void Pet::updateMove(const sf::Time& delta_time, sf::Vector2f parent_pos)
{
	sf::Vector2f dir = parent_pos - this->getPosition();

	this->sprite.move((dir.x * this->mov_speed * delta_time.asSeconds()), (dir.y * this->mov_speed * delta_time.asSeconds()));
	hit_box.setPosition(getPosition());
}

void Pet::updateRotate(sf::Vector2f target)
{
	float dX = target.x - getPosition().x;
	float dY = target.y - getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg + 270.f);
}

void Pet::updateHud()
{
	hud.updateText(hp, getPosition());
}

void Pet::initVar()
{
	mov_speed_default = 1;
	mov_speed = mov_speed_default;

	hp_max = 25;
	hp = hp_max;
}

void Pet::initSprite(const sf::Texture & texture, sf::Vector2f spawn_pos)
{
	sprite.setTexture(texture);     //TEXTURE
	sprite.setScale(0.1f, 0.1f);      //SCALE
	sprite.setPosition(spawn_pos);  //POS
	sprite.setOrigin(222.f, 188.f);      //ORIGIN
}

void Pet::initHitbox()
{
	hit_box.setSize(sf::Vector2f(445, 377));     //SIZE
	hit_box.setOutlineColor(sf::Color::Transparent); //COLOR
	hit_box.setOutlineThickness(3.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());           //SCALE
	hit_box.setPosition(getPosition());              //POS
	hit_box.setOrigin(222.f, 188.f);                       //ORIGIN
}
