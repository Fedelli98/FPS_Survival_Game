#ifndef ENTITY_H
#define ENTITY_H

#include "TileMap.h"
#include "CollisionManager.h"
#include "MovementComponent.h"

namespace BulletOwner
{
	enum Owner { Player, Boss, Pet };
}

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void render(std::shared_ptr<sf::RenderWindow> target);
	virtual void update(const float& dt);

	sf::Vector2f getPosition();
	void         setPosition(sf::Vector2f pos);

	sf::RectangleShape getHitBox();

	GridLocation getGridPos();
	void         setGridPosition(float tilesize);

	void  setMoveSpeed(float mov_speed);
	float getMovSpeed();
	void  setMoveSpeedDef(float mov_speed_def);
	float getMovSpeedDef();

	const sf::Sprite& getSprite();

	CollisionManager collision_manager;

protected:
	//Functions
	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *vec);
	void initMovemenComponent(const float maxvelocity, const float accelleration, const float decelleration);

	//Variables
	sf::Sprite sprite;
	sf::RectangleShape hit_box;

	GridLocation gridpos;

	std::shared_ptr<MovementComponent> movementcomponent;
	float mov_speed;
	float mov_speed_default;
};

#endif
