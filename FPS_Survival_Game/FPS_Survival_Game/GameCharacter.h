#pragma once
#include"SFML/Graphics.hpp"
#include"TextureHolder.h"
#include"Hud.h"

class GameCharacter
{
public:
	GameCharacter();
	virtual ~GameCharacter();

	void render(sf::RenderWindow* target);

	sf::Vector2f getPosition();

	sf::RectangleShape hit_box;
	void takeDamage(/*TIPO DEL PROIETTILE DA CUI VIENE COLPITO*/);

	int getHp();

	int getAmmo();
	void setAmmo(int a);
	void decreaseAmmo();

protected:

	bool sat_test(const sf::FloatRect &rectSp1, const sf::FloatRect &rectSp2, sf::Vector2f *out_mtv);

	sf::Sprite _sprite;
	sf::Vector2f out_mtv;

	Hud gui;

	int hp;
	int ammo;
	int max_ammo;
	bool hit;
	bool is_reloading;

	float mov_speed;


};

