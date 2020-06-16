#include "Bullet.h"

Bullet::Bullet(BulletOwner::Owner owner, sf::Vector2f owner_pos,const sf::Texture & texture)
{
	this->owner = owner;

	this->mov_speed = 1500;

	switch(owner)
	{
	case(BulletOwner::Player):
		initSpritePlayer(owner_pos, texture);
		initHitBox();
		this->allied = true;
		break;

	case(BulletOwner::Boss):
		initSpriteBoss(owner_pos, texture);
		initHitBox();
		this->allied = false;
		break;

	case(BulletOwner::Pet):
		initSpritePet(owner_pos, texture);
		initHitBox();
		this->allied = true;
		break;
	}

	damage = 1;
}

Bullet::Bullet()
{
}

Bullet::~Bullet()
{
}

void Bullet::calculateDir(sf::Vector2f owner_pos, sf::Vector2f target)
{
	float dx;
	float dy;
	float lenght;
	sf::Vector2f normVect;

	switch (this->owner)
	{
	case(BulletOwner::Pet):
		dx = target.x - owner_pos.x;
		dy = target.y - owner_pos.y;
		sprite.setPosition(owner_pos);
		hit_box.setPosition(sprite.getPosition());
		break;
	case(BulletOwner::Boss):
		dx = target.x - owner_pos.x;
		dy = target.y - owner_pos.y;
		sprite.setPosition(owner_pos);
		hit_box.setPosition(sprite.getPosition());
		break;
	}

	lenght = sqrt(pow(dx, 2) + pow(dy, 2));
	normVect = sf::Vector2f(dx / lenght, dy / lenght);
	this->dir = normVect;
}

void Bullet::setDir(sf::Vector2f dir)
{
	this->dir = dir;
}

bool Bullet::isAllied()
{
	return
		this->allied;
}

int Bullet::getDamage()
{
	return damage;
}

BulletOwner::Owner Bullet::getOwner()
{
	return
		this->owner;
}

void Bullet::initSpritePet(sf::Vector2f owner_pos, const sf::Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(owner_pos);
	sprite.setScale(0.013f, 0.013f);
	this->sprite.setOrigin(-500, 0);
}

void Bullet::initSpriteBoss(sf::Vector2f owner_pos, const sf::Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(owner_pos);
	sprite.setScale(0.013f, 0.013f);
	this->sprite.setOrigin(-3500, -562);
}

void Bullet::initSpritePlayer(sf::Vector2f owner_pos, const sf::Texture & texture)
{
	sprite.setTexture(texture);
	sprite.setPosition(owner_pos);
	sprite.setScale(0.013f, 0.013f);
	this->sprite.setOrigin(-3500, -562);
}

void Bullet::initHitBox()
{
	hit_box.setSize(sf::Vector2f(813.f, 306.f));
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(10.f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setPosition(this->getPosition());
	hit_box.setScale(sprite.getScale());
	hit_box.setOrigin(sprite.getOrigin());
}

void Bullet::updateMove(const sf::Time& delta_time)
{
	this->sprite.move(this->dir.x * this->mov_speed * delta_time.asSeconds(), this->dir.y * this->mov_speed * delta_time.asSeconds());
	hit_box.setPosition(sprite.getPosition());
}

void Bullet::updateRotate()
{
	const float PI = 3.14159265f;
	float deg = atan2(dir.y, dir.x) * 180.f / PI;

	this->sprite.setRotation(deg);
	this->hit_box.setRotation(deg);
}