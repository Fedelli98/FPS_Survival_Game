#include "GameState.h"

void GameState::initKeybinds()
{
	std::fstream ifs("Config/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();

	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");

	std::cout << "\n \n \n" << std::endl;
	for (auto &i : this->keybinds)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void GameState::updateState()
{
	//GAMEOVER
	if (player)
		if (player->getHp() < 0)
		{
			this->states->top()->endState();
		}

	//PAUSE MENU
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		this->states->push(new PauseMenu(this->window, &this->keybinds, this->states));
		return;
	}
}

void GameState::updateAchievement(const sf::Time & delta_time)
{
	achievement->updateBadge(delta_time);
}

void GameState::updatePlayer(const sf::Time & delta_time)
{
	sf::Vector2f dir;

	player->updateMove(delta_time);
	player->updateMovSpeed(delta_time);
	player->updateHud();

	player->updateRotate(mouse_pos_view);

	//collisionwalls
	dir = collision.CollideWithWalls(player->getHitBox().getGlobalBounds(), tile_map.findWalls(static_cast<int>(player->getPosition().x), static_cast<int>(player->getPosition().y)));
	if (collision.isCollide())
	{
		player->setPosition(player->getPosition() + dir);
		collision.reset();
	}

	if (player->updateReload(delta_time))
	{
		sf::IntRect rect_m;
		sf::IntRect rect_s;

		sf::IntRect rect(0, 0, textures->get(player->getId()).getSize().x / 5,
			textures->get(player->getId()).getSize().y / 4);
		player->setTexturesSprite(textures->get(player->getId()), &rect);
		if (player->getId() == Textures::HandgunP)
		{
			rect_m = sf::IntRect(0, 0, textures->get(Textures::HandgunP).getSize().x / 5,
				textures->get(Textures::HandgunP).getSize().y / 4);
			rect_s = sf::IntRect(0, 0, textures->get(Textures::Handgun_S).getSize().x / 3,
				textures->get(Textures::Handgun_S).getSize().y);
		}
		else if (player->getId() == Textures::RifleP)
		{
			rect_m = sf::IntRect(0, 0, textures->get(Textures::RifleP).getSize().x / 5,
				textures->get(Textures::RifleP).getSize().y / 4);
			rect_s = sf::IntRect(0, 0, textures->get(Textures::Rilfe_S).getSize().x / 3,
				textures->get(Textures::Rilfe_S).getSize().y);
		}
		else if (player->getId() == Textures::ShotgunP)
		{
			rect_m = sf::IntRect(0, 0, textures->get(Textures::ShotgunP).getSize().x / 5,
				textures->get(Textures::ShotgunP).getSize().y / 4);
			rect_s = sf::IntRect(0, 0, textures->get(Textures::Shotgun_S).getSize().x / 3,
				textures->get(Textures::Shotgun_S).getSize().y);
		}
		player->walk_animator->reset();
		player->shoot_animator->reset();
		player->walk_animator->setRect(rect_m);
		player->shoot_animator->setRect(rect_s);
	}

	if (player->shooting(delta_time))
	{
		spawnBullet(BulletOwner::Player);
		Textures::SHOOT txt;
		if (player->getId() == Textures::RifleP)
			txt = Textures::Rilfe_S;
		else if (player->getId() == Textures::ShotgunP)
			txt = Textures::Shotgun_S;
		else
			txt = Textures::Handgun_S;
		player->setTexturesSprite(textures->get(txt));
	}
	else if (player->getTexture() != &textures->get(player->getId()))
	{
		player->setTexturesSprite(textures->get(player->getId()));
		player->shoot_animator->reset();
	}
}

void GameState::updateRound()
{
	if (round.getKills() == round.getKillsPerRound())
	{
		for (unsigned int i = 0; i < enemies.size(); i++)
		{
			enemies.erase(enemies.begin(), enemies.end());
		}

		enemies_alive = 0;
		round.setKills(0);
		round.reset();
		round.increaseRound();

		if (round.getCounterRound() % round.getRoundPerBoss() == 0)
			round.setBossRound(true);
	}
}

void GameState::spawnZombies(const sf::Time & delta_time)
{
	while (enemies_alive != max_enemies)
	{
		this->enemies.emplace_back(new Enemy(textures->get(Textures::Enemy), grid, tile_map.getGridSize()));
		enemies_alive++;
	}

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		updateZombie(delta_time, i);

		if ((enemies[i]->getHp() <= 0))
		{
			animations.emplace_back(new Animation(textures->get(Textures::Blood), Textures::Blood, enemies[i]->getHitBox().getPosition(), 2,
				textures->get(Textures::Blood).getSize(), sf::Vector2u(3, 1), 3 / 4.f));
			animations.emplace_back(new Animation(textures->get(Textures::Coin), Textures::Coin, enemies[i]->getHitBox().getPosition(), 10,
				textures->get(Textures::Coin).getSize(), sf::Vector2u(4, 1), 0.5f, sf::Vector2f(0.1f, 0.1f)));
			enemies.erase(enemies.begin() + i);
			enemies_alive--;
			round.increaseKills();
		}
	}
}

void GameState::updateZombie(const sf::Time & delta_time, int i)
{
	if (!enemies[i]->collision_manager.isCollide())
		enemies[i]->updateMove(delta_time, player->getPosition(), tile_map.getGridSize());
	else if (enemies[i]->_m.getTarget() != player->getPosition())
		enemies[i]->_m.setTarget(player->getPosition());

	enemies[i]->updateRotate(player->getPosition());
	enemies[i]->updateHud();

	//petCollision
	if (pet_alive)
	{
		collision.CollideWithEntity(enemies[i]->getHitBox().getGlobalBounds(), pet->getHitBox().getGlobalBounds());
		if (collision.isCollide())
			pet->takeDamage();
		collision.reset();
	}

	//playercollision
	sf::Vector2f dir = enemies[i]->collision_manager.CollideWithEntity(enemies[i]->getHitBox().getGlobalBounds(), player->getHitBox().getGlobalBounds());
	if (enemies[i]->collision_manager.isCollide())
	{
		if (!enemies[i]->shoot_animator.isActive())
		{
			sf::IntRect rect(0, 0, textures->get(Textures::Enemy_Attack).getSize().x / 3,
				textures->get(Textures::Enemy_Attack).getSize().y / 3);

			enemies[i]->setTexturesSprite(textures->get(Textures::Enemy_Attack), &rect);
			enemies[i]->animator.reset();
			enemies[i]->shoot_animator.setRect(rect);
			enemies[i]->updateSpriteAttack(delta_time);

		}
		else
		{
			enemies[i]->updateSpriteAttack(delta_time);
		}
		if (enemies[i]->canHit(delta_time))
		{
			player->takeDamage();
		}
	}
	else if (enemies[i]->shoot_animator.isActive())
	{
		enemies[i]->shoot_animator.reset();
		sf::IntRect rect(0, 0, textures->get(Textures::Enemy).getSize().x / 5,
			textures->get(Textures::Enemy).getSize().y / 4);
		enemies[i]->setTexturesSprite(textures->get(Textures::Enemy), &rect);
	}
}

void GameState::spawnBoss(const sf::Time & delta_time)
{
	round.startCountdown(delta_time);

	if (!round.isLoading() && round.isBossRound())
	{
		if (!boss_alive)
		{
			std::shared_ptr<Boss>boss(new Boss(grid, textures->get(Textures::Boss)));
			this->boss = boss;
			this->boss_alive = true;
			if (store != NULL)
				store->setClosed(false);
		}

		updateBoss(delta_time);

		if ((boss->getHp() <= 0))
		{
			spawnPet();

			//RESET BOSS AND ROUND
			boss.reset();

			round.setBossRound(false);
			this->boss_alive = false;
			round.increaseBoss();
			round.setKills(0);
			round.reset();
			round.increaseRound();
		}
	}
}

void GameState::updateBoss(const sf::Time & delta_time)
{
	if (!boss->isShoot())
		boss->updateMove(delta_time, player->getPosition(), tile_map.getGridSize());

	if (boss->shooting(delta_time, player->getPosition()))
		spawnBullet(BulletOwner::Boss);

	boss->updateRotate(player->getPosition());
	boss->updateReload(delta_time);
	boss->updateHud();
}

void GameState::spawnPet()
{
	if (!pet_alive)
	{
		this->pet = std::make_shared<Pet>(textures->get(Textures::Pet), boss->getPosition());
		this->pet_alive = true;
	}
	else
		pet->boostHeal();
}

void GameState::updatePet(const sf::Time & delta_time)
{
	if (pet_alive)
	{
		pet->updateMove(delta_time, player->getPosition());
		pet->updateRotate(mouse_pos_view);

		if (player->isShoot())
			spawnBullet(BulletOwner::Pet);

		pet->updateHud();

		//playerCollision
		sf::Vector2f dir = collision.CollideWithEntity(pet->getHitBox().getGlobalBounds(), player->getHitBox().getGlobalBounds());
		if (collision.isCollide())
			pet->setPosition(pet->getPosition() + dir);
		collision.reset();

		//PET DEATH
		if (pet->getHp() <= 0)
		{
			this->pet.reset();
			this->pet_alive = false;
		}
	}
}

void GameState::spawnBullet(BulletOwner::Owner owner)
{
	if (owner == BulletOwner::Player)
	{
		player->getStf()->shot(bullets, owner, player->getPosition(), mouse_pos_view, textures->get(Textures::Proiettile));
		player->setAmmo(player->getAmmo() - player->getStf()->nrshot);
		if ((player->getAmmo() - player->getStf()->nrshot) < 0)
			player->getStf()->nrshot = player->getAmmo();
	}
	if (owner == BulletOwner::Boss)
	{
		std::shared_ptr<Bullet>bullet(new Bullet(BulletOwner::Boss, boss->getPosition(), textures->get(Textures::Proiettile)));
		boss->setAmmo(boss->getAmmo() - 1);
		bullets.emplace_back(bullet);
		bullet->calculateDir(boss->getPosition(), player->getPosition());
	}
	if (owner == BulletOwner::Pet)
	{
		player->getStf()->shot(bullets, owner, pet->getPosition(), mouse_pos_view, textures->get(Textures::Proiettile));
		if ((player->getAmmo() - player->getStf()->nrshot) < 0)
			player->getStf()->nrshot = player->getAmmo();
	}
}

void GameState::updateBullet(const sf::Time & delta_time)
{
	if (!bullets.empty())
	{
		for (unsigned int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->updateRotate();

			//ALLIED
			if (bullets[i]->isAllied())
			{
				//collisonZombies
				if (!enemies.empty())
				{
					for (int j = 0; j != enemies.size(); j++)
					{
						collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), enemies[j]->getHitBox().getGlobalBounds());
						if (collision.isCollide())
						{
							enemies[j]->takeDamage(bullets[i]->getDamage());
							bullets.erase(bullets.begin() + i);
							j = (enemies.size() - 1);
						}
					}
				}

				//collisionBoss
				if (boss_alive)
				{
					collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), boss->getHitBox().getGlobalBounds());
					if (collision.isCollide())
					{
						boss->takeDamage();
						bullets.erase(bullets.begin() + i);
					}
				}
			}
			else //!ALLIED
			{
				//collisionPlayer
				collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), player->getHitBox().getGlobalBounds());
				if (collision.isCollide())
				{
					player->takeDamage();
					bullets.erase(bullets.begin() + i);
				}
				else
				{
					if (pet_alive)
					{
						//collisionPet
						collision.CollideWithEntity(bullets[i]->getHitBox().getGlobalBounds(), pet->getHitBox().getGlobalBounds());
						if (collision.isCollide())
						{
							pet->takeDamage();
							bullets.erase(bullets.begin() + i);
						}
					}
				}
			}

			//WALLS
			if (collision.isCollide())
				collision.reset();
			else
			{
				collision.CollideWithWalls(bullets[i]->getHitBox().getGlobalBounds(), tile_map.findWalls(static_cast<int>(bullets[i]->getPosition().x), static_cast<int>(bullets[i]->getPosition().y)));
				if (collision.isCollide())
				{
					collision.reset();
					bullets.erase(bullets.begin() + i);
				}
				else
					bullets[i]->updateMove(delta_time);
			}
		}
	}
}

void GameState::updateBoost()
{	
	//SPAWN
	if (boost_manager.canSpawn())
	{
		boost_manager.spawn();
	}

	////UPDATE BOOST
	int b_type = boost_manager.checkCollisionType(player->getHitBox().getGlobalBounds());
	player->boost(BoostType::Type(b_type));
}

void GameState::updateAnimations(const sf::Time & delta_time)
{
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		animations[i]->setShapeTxtRect(animations[i]->update(delta_time));
		animations[i]->updateTimer(delta_time);
		if (animations[i]->getId() == Textures::Coin)
		{
			collision.CollideWithEntity(animations[i]->getShape().getGlobalBounds(), player->getHitBox().getGlobalBounds());
			if (collision.isCollide())
			{
				player->pickUpCoins();
				animations.erase(animations.begin() + i);
				collision.reset();
			}
		}
		else
			if (animations[i]->getTimer() <= 0/* || animations[i]->isEndAnimation()*/)
				animations.erase(animations.begin() + i);
	}
}

void GameState::updateGameView(const sf::Time & delta_time)
{
	sf::Vector2f dir = player->getPosition() - game_view.getCenter();
	if ((game_view.getCenter().x + (game_view.getSize().x / 2) + (dir.x * delta_time.asSeconds() * this->game_view_speed)) > tile_map.getSize().x
		|| game_view.getCenter().x - (game_view.getSize().x / 2) + (dir.x * delta_time.asSeconds() * this->game_view_speed) < 0)
		dir.x = 0;
	if ((game_view.getCenter().y + (game_view.getSize().y / 2) + (dir.y * delta_time.asSeconds() * this->game_view_speed)) > tile_map.getSize().y
		|| game_view.getCenter().y - (game_view.getSize().y / 2) + (dir.y * delta_time.asSeconds() * this->game_view_speed) < 0)
		dir.y = 0;
	if (dir != sf::Vector2f(0, 0))
		game_view.move(dir * delta_time.asSeconds() * this->game_view_speed);
	window->setView(game_view);

}

void GameState::updateHud()
{
	hud.updateText(round.getKills(), round.getCountdown().asSeconds(), round.getCounterRound(), player->getCoins(), game_view);
}

void GameState::renderEnemies()
{
	if (!round.isLoading() && !round.isBossRound())
	{
		for (auto i = enemies.begin(); i != enemies.end(); i++)
		{
			(*i)->render(window);
			(*i)->renderHud(window);
		}
	}
}

//															R E N D E R


void GameState::renderPlayer()
{
	player->renderHud(window);
	player->render(window);
}

void GameState::renderBoss()
{
	if (boss_alive)
	{
		boss->renderHud(window);
		boss->render(window);
	}
}

void GameState::renderPet()
{
	if (pet_alive)
	{
		pet->renderHud(window);
		pet->render(window);
	}
}

void GameState::renderBullets()
{
	for (int i = 0; i != bullets.size(); i++)
	{
		bullets[i]->render(this->window);
	}
}

void GameState::renderBoosts()
{
	boost_manager.renderBoosts(window);
}

void GameState::renderAchievement()
{
	if (achievement->isKillsOn())
	{
		achievement->renderKillsBadge(this->window, this->game_view);
	}

	if (achievement->isRoundOn())
	{
		achievement->renderRoundBadge(this->window, this->game_view);
	}

	if (this->achievement->isBossOn())
	{
		achievement->renderBossBadge(this->window, this->game_view);
	}
}

void GameState::renderAnimations()
{
	for (int i = 0; i != animations.size(); i++)
	{
		animations[i]->render(this->window);
	}
}


//				***********				INITIALIZATION				***********
void GameState::playerInit(Textures::ID id, std::shared_ptr<StrategyFight> stf)
{
	std::shared_ptr<TileSheetAnimator> walk_animator = std::make_shared<TileSheetAnimator>(textures->get(id).getSize(), sf::Vector2u(5, 4), sf::Vector2u(0, 0), 1 / 60.f);
	this->player = std::make_shared<PlayerT>(textures->get(id), id, stf, walk_animator);
	Textures::SHOOT texture;
	if (id == Textures::RifleP)
		texture = Textures::Rilfe_S;
	else
		if (id == Textures::ShotgunP)
			texture = Textures::Shotgun_S;
		else
			texture = Textures::Handgun_S;

	this->player->shoot_animator = std::make_shared<TileSheetAnimator>(textures->get(texture).getSize(), sf::Vector2u(3, 1), sf::Vector2u(0, 0), 1 / 12.f);
}

void GameState::gridInit()
{
	this->grid.initGrid(tile_map.getObstacle());
}

void GameState::gameViewInit()
{
	this->game_view.setCenter(player->getPosition());
}

void GameState::textureInit()
{
	this->textures = std::make_shared<TextureHolder>();
	//GENERAL TEXTURE 
	textures->load(Textures::Enemy, "Sources/Zombie_move.png");
	textures->load(Textures::Proiettile, "Sources/bullets/bullet1.png");
	textures->load(Textures::Boss, "Sources/boss/boss.png");
	textures->load(Textures::Personaggio, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	textures->load(Textures::ShotgunP, "Sources/Top_Down_Survivor/shotgun/move_sheet_shotgun.png");
	textures->load(Textures::RifleP, "Sources/Top_Down_Survivor/rifle/move_sheet_rifle.png");
	textures->load(Textures::HandgunP, "Sources/Top_Down_Survivor/handgun/move_sheet_handgun.png");
	textures->load(Textures::Pet, "Sources/pet.png");
	textures->load(Textures::HP, "Sources/hp.png");
	textures->load(Textures::MS, "Sources/ms.png");
	textures->load(Textures::Blood, "Sources/blood.png");
	textures->load(Textures::Coin, "Sources/coin_animation.png");

	//SHOOTING TEXTURE
	textures->load(Textures::Rilfe_S, "Sources/Top_Down_Survivor/rifle/shoot_sheet_rifle.png");
	textures->load(Textures::Shotgun_S, "Sources/Top_Down_Survivor/shotgun/shoot_sheet_shotgun.png");
	textures->load(Textures::Handgun_S, "Sources/Top_Down_Survivor/handgun/shoot_sheet_handgun.png");

	textures->load(Textures::Enemy_Attack, "Sources/Zombie_Attack.png");
}

void GameState::varInit()
{
	this->enemies_alive = 0;
	this->boss_alive = false;
	this->pet_alive = false;
}

//				***********				CONSTRUCTOR					***********

GameState::GameState(sf::Vector2i mapsize, std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,
	Textures::ID id, std::shared_ptr<StrategyFight> stf) : State(window, supportedKeys, states), game_view(sf::Vector2f(0.f, 0.f), sf::Vector2f(1320, 900)),
	tile_map(mapsize), grid(mapsize.x, mapsize.y)
{
	this->ID = GameStates::Game;
	textureInit();
	boost_manager.setTextures(textures->get(Textures::HP), textures->get(Textures::MS));
	playerInit(id, stf);
	gridInit();
	varInit();
	gameViewInit();
	achievement = new Achievement(&round);
	this->initKeybinds();
}

GameState::~GameState()
{
}


void GameState::updateInput(const float & dt)
{
}

void GameState::update(const sf::Time& delta_time)
{
	this->updateInput(delta_time.asSeconds());
	//STORE 
	if ((round.getCountdown().asSeconds() <= 2 && round.getCountdown().asSeconds() >= 1.f) && round.isBossRound())
	{
		if (store == NULL)
		{
			this->store = new Store(this->window, &this->keybinds, this->states, player);
			this->states->push(store);
		}
		else if (store != NULL)
		{
			if (!store->Closed())
				store->open();
		}
	}
	/*if (store == NULL || (store != NULL && store->Closed()))
	{*/
	updateMousePos();

	updateAchievement(delta_time);

	updateHud();

	updatePlayer(delta_time);

	updateRound();

	if (!round.isLoading() && !round.isBossRound())
		spawnZombies(delta_time);
	else
		spawnBoss(delta_time);

	updatePet(delta_time);

	updateBoost();

	updateBullet(delta_time);

	updateAnimations(delta_time);

	updateGameView(delta_time);

	updateState();
	/*}*/
}

void GameState::update(const sf::Time & delta_time, sf::Event event)
{
	throw std::runtime_error("Unexpected error");
	return;
}

void GameState::render(std::shared_ptr<sf::RenderWindow> target)
{
	if (!target)
		target = this->window;
	
	tile_map.render(window);

	renderBoosts();
	renderAnimations();
	renderPlayer();
	renderPet();
	renderEnemies();
	renderBoss();
	renderBullets();

	hud.renderTextsHud(window);

	renderAchievement();
}
