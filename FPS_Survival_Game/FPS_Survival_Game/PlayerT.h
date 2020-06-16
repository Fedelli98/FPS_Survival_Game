#pragma once
#include "Character.h"
#include "TextureHolder.h"
#include "boost.h"
#include "StrategyFight.h"
#include "TileSheetAnimator.h"

class StrategyFight;

class PlayerT : public Character
{
public:
	PlayerT(const sf::Texture& texture, Textures::ID id, std::shared_ptr<StrategyFight> stf, std::shared_ptr<TileSheetAnimator> walk_animator);

	PlayerT();
	virtual ~PlayerT();

	void updateMove(const sf::Time& delta_time);
	void updateRotate(sf::Vector2f target);
	bool updateReload(const sf::Time& delta_time);
	void updateMovSpeed(const sf::Time& delta_time);
	void updateSpriteAttack(const sf::Time& delta_time);
	void updateHud();

	void boost(BoostType::Type b_type);
	void pickUpCoins(int coins = 1);
	int getCoins();

	bool shooting(const sf::Time& delta_time);
	bool isShooting();
	void setStrategyFight(std::shared_ptr<StrategyFight> stf);

	Textures::ID getId();
	std::shared_ptr<StrategyFight> getStf();

	std::shared_ptr<TileSheetAnimator> walk_animator;
	std::shared_ptr<TileSheetAnimator> shoot_animator;

	const sf::Texture* getTexture();

private:

	void initVar();
	void initSprite(const sf::Texture& texture);
	void initHitBox();
	void initType();

private:
	Textures::ID id;
	CharacterType::Type type;

	std::shared_ptr<StrategyFight> stf;
	const float ms_cd = 3.f;
	float ms_clock;
	int coins = 0;
};

