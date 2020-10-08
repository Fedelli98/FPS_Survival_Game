#include "Store.h"
#include <iostream>
#include <string>

Store::Store(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states, std::shared_ptr<PlayerT> player)
	: State(window, supportedKeys, states)
{
	this->ID = GameStates::Menu;
	this->player = player;
	this->closed = false;
	this->window = window;

	initBackground();
	initTextures();
	initButtons();

	//COINS
	coinsfont.loadFromFile("Fonts/edunline.ttf");
	//PlayerCoins
	playercoins.setFont(coinsfont);
	std::string coins = std::to_string(player->getCoins());
	playercoins.setString(coins);
	playercoins.setFillColor(sf::Color::Yellow);
	playercoins.setCharacterSize(48);
	playercoins.setPosition(background.getPosition() + sf::Vector2f(40, 176));
	//Coins
	this->coins.setFont(coinsfont);
	this->coins.setString("COINS");
	this->coins.setFillColor(sf::Color::Yellow);
	this->coins.setCharacterSize(48);
	this->coins.setPosition(background.getPosition() + sf::Vector2f(40, 128));
}

Store::~Store()
{
}

void Store::initKeybinds()
{
}

void Store::open()
{
	State* tmp;
	State* tmp1;
	tmp = states->top();
	states->pop();
	tmp1 = states->top();
	states->top() = tmp;
	states->push(tmp1);
	std::string coins = std::to_string(player->getCoins());
	playercoins.setString(coins);
}

void Store::setClosed(bool close)
{
	this->closed = close;
}

bool Store::Closed()
{
	return this->closed;
}

void Store::updateInput(const float & dt)
{
}

void Store::update(const sf::Time & delta_time, sf::Event event)
{
	//window->setView(window->getDefaultView());
	updateMousePos();
	updateButtons(event);
	updateEvents(event);
	/*if (!this->states->top()->getQuit())
		render();*/
}

void Store::update(const sf::Time& delta_time)
{
	throw std::runtime_error("Unexpected error");
	return;
}

void Store::render(std::shared_ptr<sf::RenderWindow> target)
{
	window->clear();
	window->draw(background);
	window->draw(playercoins);
	window->draw(coins);
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->draw(target);
	}
	window->display();
}

void Store::initButtons()
{
	//HEALTH
	this->buttons["HEALTH"] = std::make_unique<Button>
		("Fonts/edunline.ttf", "", sf::Color::Transparent, 0, sf::Vector2f(0, 0),
			sf::Vector2f(128, 128), sf::Color::Transparent, 0.f, sf::Color::Transparent,
			sf::Vector2f(160, 320) + background.getPosition(), textures->get(Textures::HP));
	health.button = *buttons.at("HEALTH");
	health.price = 3;

	//ESC
	this->buttons["ESC"] = std::make_unique<Button>
		("Fonts/edunline.ttf", "", sf::Color::Transparent, 0, sf::Vector2f(0.f, 0.f),
			sf::Vector2f(64, 64), sf::Color::Transparent, 0.f, sf::Color::Transparent,
			sf::Vector2f(736, 160) + background.getPosition(), textures->get(Textures::Esc));

}

void Store::initBackground()
{
	background_txt.loadFromFile("Sources/Store.png");
	background.setTexture(background_txt);
	sf::Vector2f pos;
	pos = sf::Vector2f(window->getView().getCenter().x - (background_txt.getSize().x / 2), window->getView().getCenter().y - (background_txt.getSize().y / 2));
	background.setPosition(pos);
}

void Store::initTextures()
{
	this->textures = std::make_shared<TextureHolder>();
	textures->load(Textures::HP, "Sources/hp.png");
	textures->load(Textures::Esc, "Sources/Esc.png");
}

void Store::updateEvents(sf::Event _event)
{
	if (this->buttons.at("ESC")->getState() == BTN_PRESSED)
	{
		if (states->size() > 1)
		{
			State* tmp;
			State* tmp1;
			tmp = states->top();
			states->pop();
			tmp1 = states->top();
			states->pop();
			states->push(tmp);
			states->push(tmp1);
			this->closed = true;
		}
		else states->top()->endState();
	}
}

void Store::updateButtons(sf::Event _event)
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->update(mouse_pos_view, _event);
	}

	//HEALTH
	if (this->buttons.at("HEALTH")->getState() == BTN_PRESSED)
	{
		if (player->getCoins() >= health.price)
		{
			player->setHpMax(player->getHpMax() + 50);
			player->setHp(player->getHpMax());
			player->pickUpCoins(-health.price);
			std::string coins = std::to_string(player->getCoins());
			playercoins.setString(coins);
			health.price *= 2;
		}
	}		
}
