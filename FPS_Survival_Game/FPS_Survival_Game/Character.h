#pragma once
#include "Entity.h"
#include "Hud.h"
#include "TileSheetAnimator.h"
#include <math.h>

namespace CharacterType
{
	enum Type { Shotgun, Rifle, Handgun, Player};
}

class Character :
	public Entity
{
public:
	Character();
	virtual ~Character();

	void renderHud(std::shared_ptr<sf::RenderWindow> target);

	void takeDamage(int dmg = 1);
	void boostHeal();
	
	void setHp(int hp);
	void setHpMax(int hp_max);
	void setAmmo(int i);
	void setRatioCd(const sf::Time& ratio);

	int            getHp();
	int            getHpMax();
	int            getAmmo();
	const sf::Time getRatioCd();

	void setTexturesSprite(const sf::Texture& texture, sf::IntRect* rect = NULL);

	bool isShoot();

protected:
	Hud hud;

	sf::Time reload_cd;
	sf::Time reload_clock;

	sf::Time ratio_cd;
	sf::Time ratio_clock;

	int hp;
	int hp_max;

	int ammo;
	int ammo_max;

	bool reloading = false;
	bool shoot;

};