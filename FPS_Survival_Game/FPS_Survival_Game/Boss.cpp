#include "Boss.h"

Boss::Boss(const GridNode& grid, const sf::Texture& texture) :
	_m(grid, max_distance)
{
	initVar();
	initSprite(grid, texture);
	initHitBox();
	_m.setMaxDist(max_distance);
}

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::updateMove(const sf::Time& delta_time, sf::Vector2f target, float grid_size)
{
	if (!isInRange(getPosition(), target))
	{
		this->sprite.move(_m.move(delta_time, getPosition(), target, move_vect, mov_speed));

		hit_box.setPosition(getPosition());
		setGridPosition(grid_size);
	}
}

bool Boss::shooting(const sf::Time& delta_time, sf::Vector2f target)
{
	ratio_clock -= delta_time;

	if (isInRange(getPosition(), target) && !reloading)
	{
		if (ratio_clock < sf::seconds(0.f))
		{
			ratio_clock = ratio_cd;
			shoot = true;
			if (this->ammo)
				return true;
		}
		else
			shoot = false;
		return shoot;
	}
	else
		shoot = false;
	return shoot;
}

void Boss::updateRotate(sf::Vector2f target)
{
	float dX = target.x - this->sprite.getPosition().x;
	float dY = target.y - this->sprite.getPosition().y;
	const float PI = 3.14159265f;
	float deg = atan2(dY, dX) * 180.f / PI;

	this->sprite.setRotation(deg);
}

void Boss::updateReload(const sf::Time& delta_time)
{
	if (ammo == 0)
	{
		reloading = true;
		reload_clock -= delta_time;

		if (reload_clock < sf::seconds(0.f))
		{
			ammo = ammo_max;
			reload_clock = reload_cd;
			reloading = false;
		}
	}
}

void Boss::updateHud()
{
	hud.updateText(hp, getPosition());
}

bool Boss::isInRange(sf::Vector2f obj1, sf::Vector2f obj2)
{
	float dx = obj1.x - obj2.x;
	float dy = obj1.y - obj2.y;
	float lenght = sqrt(pow(dx, 2) + pow(dy, 2));

	if (fabs(lenght) < range)
		return true;
	else
		return false;
}

void Boss::initVar()
{
	mov_speed_default = 150;
	mov_speed = mov_speed_default;

	hp_max = 200;
	hp = hp_max;

	reload_cd = sf::seconds(2.f); //DA SCEGLIERE
	reload_clock = reload_cd;

	ammo_max = 200;  // DA SCEGLIERE
	ammo = ammo_max;

	ratio_cd = sf::seconds(1.f / 7.f); //DA SCEGLIERE
	ratio_clock = ratio_cd;

	reloading = false;
}

void Boss::initSprite(const GridNode& grid,const sf::Texture& texture)
{
	sprite.setTexture(texture);
	sprite.setScale(1.5, 1.5);
	int k = rand() % 17 + 1;//max 1920
	int j = rand() % 13 + 1;//max 1080
	GridLocation pos = { k , j };
	while (!grid.getGrid()[j][k].walkable)
	{
		j++;
		k++;
	}
	sprite.setPosition(32 + k * 64.f, 32 + j * 64.f);
	sprite.setOrigin(+18, +16);
}

void Boss::initHitBox()
{
	hit_box.setSize(sf::Vector2f(36.f, 36.f));
	hit_box.setOutlineColor(sf::Color::Transparent);
	hit_box.setOutlineThickness(0.1f);
	hit_box.setFillColor(sf::Color::Transparent);
	hit_box.setScale(sprite.getScale());
	hit_box.setPosition(getPosition());
	hit_box.setOrigin(18, 16);
}
