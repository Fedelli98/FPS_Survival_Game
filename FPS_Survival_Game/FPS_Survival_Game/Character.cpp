#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
}

void Character::takeDamage(int dmg)
{
	this->hp -= dmg;
}

void Character::renderHud(std::shared_ptr<sf::RenderWindow> target)
{
	hud.renderTextsCharacter(target);
}


void Character::boostHeal()
{
	if ((this->hp = this->hp + 30) > this->hp_max)
		this->hp = this->hp_max;
}

void Character::setHp(int hp)
{
	this->hp = hp;
}

int Character::getHp()
{
	return
		this->hp;
}

void Character::setHpMax(int hp_max)
{
	this->hp_max = hp_max;
}

int Character::getHpMax()
{
	return
		this->hp_max;
}

int Character::getAmmo()
{
	return
		this->ammo;
}

void Character::setAmmo(int i)
{
	this->ammo = i;
}

void Character::setRatioCd(const sf::Time& ratio)
{
	this->ratio_cd = ratio;
}

const sf::Time Character::getRatioCd()
{
	return this->ratio_cd;
}

void Character::setTexturesSprite(const sf::Texture& texture, sf::IntRect* rect)
{
	sprite.setTexture(texture);
	if (rect != NULL)
		sprite.setTextureRect(*rect);
}

bool Character::isShoot()
{
	return shoot;
}