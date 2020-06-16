#pragma once
#include "State.h"
#include "Button.h"
#include "MainMenuState.h"
#include "PlayerT.h"
#include "GameState.h"

class MainMenu;

struct Upgrade
{
	sf::Texture texture;
	Button button;
	int price;
};

class Store :
	public State
{
public:
	Store(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::shared_ptr<PlayerT> player);
	virtual ~Store();

	virtual void initKeybinds();

	void open();
	void setClosed(bool close);
	bool Closed();

	virtual void updateInput(const float& dt);

private:
	virtual void update(const sf::Time& delta_time, sf::Event) override;
	virtual void update(const sf::Time& delta_time);
	virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);

	void initButtons();
	void initBackground();
	void initTextures();

	void updateEvents(sf::Event _event);
	void updateButtons(sf::Event _event);

private:
	
	sf::Texture background_txt;
	sf::Sprite background;
	
	sf::Font coinsfont;
	sf::Text playercoins;
	sf::Text coins;

	Upgrade health;
	Upgrade speed;

	bool closed;

	std::shared_ptr<PlayerT> player;
};

