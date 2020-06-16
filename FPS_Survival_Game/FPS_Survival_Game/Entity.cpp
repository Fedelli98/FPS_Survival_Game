#include "Entity.h"



Entity::Entity()
{
	movementcomponent = NULL;
}


Entity::~Entity()
{
}

void Entity::render(std::shared_ptr<sf::RenderWindow> target)
{
	target->draw(sprite);
	target->draw(hit_box);
}

void Entity::update(const float & dt)
{
}

sf::Vector2f Entity::getPosition()
{
	sf::Vector2f pos = this->sprite.getPosition();
	return pos;
}

void Entity::setPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}
 
sf::RectangleShape Entity::getHitBox()
{
	return
		this->hit_box;
}

GridLocation Entity::getGridPos()
{
	return this->gridpos;
}

void Entity::setGridPosition(float tilesize)
{
	this->gridpos.x = static_cast<int>(this->sprite.getPosition().x / tilesize);
	this->gridpos.y = static_cast<int>(this->sprite.getPosition().y / tilesize);
	this->gridpos.walkable = false;
}

void Entity::setMoveSpeed(float mov_speed)
{
	this->mov_speed = mov_speed;
}

float Entity::getMovSpeed()
{
	return 
		this->mov_speed;
}

void Entity::setMoveSpeedDef(float mov_speed_def)
{
	this->mov_speed_default = mov_speed_def;
}

float Entity::getMovSpeedDef()
{
	return 
		this->mov_speed_default;
}

const sf::Sprite & Entity::getSprite()
{
	return this->sprite;
}


bool Entity::sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv)
{
	float proj_x, proj_y, overlap_x, overlap_y;

	// test overlap in x axis
	proj_x = std::max(rectSp1.left + rectSp1.width, rectSp2.left + rectSp2.width) - std::min(rectSp1.left, rectSp2.left);
	if (proj_x < rectSp1.width + rectSp2.width) {
		if (out_mtv) {
			// calculate mtv in x
			overlap_x = rectSp1.width + rectSp2.width - proj_x;
		}
		// test overlap in y axis
		proj_y = std::max(rectSp1.top + rectSp1.height, rectSp2.top + rectSp2.height) - std::min(rectSp1.top, rectSp2.top);
		if (proj_y < rectSp1.height + rectSp2.height) {
			if (out_mtv) {
				// calculate mtv in y
				overlap_y = rectSp1.height + rectSp2.height - proj_y;
				out_mtv->x = out_mtv->y = 0;

				// choose minimun overlap
				if (overlap_x < overlap_y) {
					out_mtv->x = overlap_x * (rectSp1.left < rectSp2.left ? -1 : 1);
				}
				else {
					out_mtv->y = overlap_y * (rectSp1.top < rectSp2.top ? -1 : 1);
				}
			}
			return true;
		}
	}
	return false;
}

void Entity::initMovemenComponent(const float maxvelocity, const float accelleration, const float decelleration)
{
	movementcomponent = std::make_shared<MovementComponent>(this->sprite, maxvelocity, accelleration, decelleration);
}
