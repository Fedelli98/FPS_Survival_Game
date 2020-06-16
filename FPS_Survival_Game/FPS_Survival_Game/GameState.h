#ifndef  GAMESTATE_H
#define  GAMESTATE_H

#include "Achievement.h"
#include "Animation.h"
#include "Boost.h"
#include "BoostManager.h"
#include "Boss.h"
#include "Collision.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "GridNode.h"
#include "Hud.h"
#include "Observer.h"
#include "PauseMenu.h"
#include "Pet.h"
#include "PlayerT.h"
#include "RoundManager.h"
#include "State.h"
#include "Store.h"
#include "StrategyFight.h"
#include "TextureHolder.h"
#include "TileMap.h"
#include <vector>

class Store;

class GameState :
	public State
{
private:
	//Funtions
	void initKeybinds();
	void updateState();

	void updateAchievement(const sf::Time& delta_time);

	void updatePlayer(const sf::Time& delta_time);
	void updateRound();

	void spawnZombies(const sf::Time& delta_time);
	void updateZombie(const sf::Time& delta_time, int i);

	void spawnBoss(const sf::Time& delta_time);
	void updateBoss(const sf::Time& delta_time);

	void spawnPet();
	void updatePet(const sf::Time& delta_time);

	void spawnBullet(BulletOwner::Owner owner);
	void updateBullet(const sf::Time& delta_time);

	void updateBoost();
	void updateAnimations(const sf::Time& delta_time);

	void updateGameView(const sf::Time& delta_time);
	void updateHud();

	void renderEnemies();
	void renderPlayer();
	void renderBoss();
	void renderPet();
	void renderBullets();
	void renderBoosts();
	void renderAchievement();
	void renderAnimations();

	void playerInit(Textures::ID id, std::shared_ptr<StrategyFight> stf);
	void gridInit();
	void gameViewInit();
	void textureInit();
	void varInit();

	TileMap tile_map;
	GridNode grid;
	sf::View game_view;
	Hud hud;
	RoundManager round;
	Achievement * achievement;
	Store* store;
	CollisionManager collision;
	BoostManager boost_manager;

	std::vector<std::shared_ptr<Enemy>> enemies;
	std::shared_ptr<PlayerT> player;
	std::shared_ptr<Boss> boss;

	std::shared_ptr<Pet> pet;
	std::vector<std::shared_ptr<Bullet>> bullets;
	std::vector<std::shared_ptr<Animation>> animations;

	int enemies_alive;
	bool boss_alive;
	bool pet_alive;

	const int max_enemies = 10;
	const float game_view_speed = 4.5f;



public:
	GameState(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
		Textures::ID id, std::shared_ptr<StrategyFight> stf);
	virtual ~GameState();

	//Functions

	void updateInput(const float& dt);
	void update(const sf::Time& delta_time);
	virtual void update(const sf::Time& delta_time, sf::Event event);
	void render(std::shared_ptr<sf::RenderWindow> target = nullptr);
};

#endif