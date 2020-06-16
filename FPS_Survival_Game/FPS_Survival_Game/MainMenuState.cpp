#include "MainMenuState.h"

void MainMenuState::initKeybinds()
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
}

void MainMenuState::initBackground()
{
	background.setTexture(&textures->get(Textures::MainMenuState));
	background.setSize(sf::Vector2f((float)textures->get(Textures::MainMenuState).getSize().x,
		(float)textures->get(Textures::MainMenuState).getSize().y));
	background.setPosition(sf::Vector2f(0, 0));
}
 
void MainMenuState::initButtons()
{
	//NEW GAME
	this->buttons["NEW_GAME"] = std::make_unique<Button>
		("Sources/edunline.ttf", "New Game", sf::Color::Black, 100.f, sf::Vector2f(660.f, 200.f),
			sf::Vector2f(500.f, 70.f), sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(660.f, 230.f));
	//SETTINGS
	this->buttons["SETTINGS"] = std::make_unique<Button>
		("Sources/edunline.ttf", "", sf::Color::Transparent, 0, sf::Vector2f(0.f, 0.f),
			sf::Vector2f((float)this->textures->get(Textures::Settings).getSize().x, 
			(float)this->textures->get(Textures::Settings).getSize().y),
			sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(0.f, 0.f), textures->get(Textures::Settings),
			sf::Vector2f(0.4f, 0.4f));
	//EDITOR
	this->buttons["EDITOR"] = std::make_unique<Button>
		("Sources/edunline.ttf", "Editor", sf::Color::Black, 100, sf::Vector2f(800.f, 400.f),
			sf::Vector2f(170.f, 50.f), sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(800.f, 430.f));
	//EXIT
	this->buttons["EXIT"] = std::make_unique<Button>
		("Sources/edunline.ttf", "Exit", sf::Color::Black, 70.f, sf::Vector2f(900.f, 600.f),
			sf::Vector2f(135.f, 50.f), sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(900.f, 620.f));
}

void MainMenuState::initTextures()
{
	this->textures = std::make_shared<TextureHolder>();
	textures->load(Textures::MainMenuState, "Sources/background.jpg");
	textures->load(Textures::Settings, "Sources/Settings-icon.png");
}

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->ID = GameStates::Menu;
	this->initTextures();
	this->initBackground();
	this->initButtons();
	this->initKeybinds();
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::updateInput(const float & dt)
{
}

void MainMenuState::updateButtons(sf::Event event)
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->update(mouse_pos_view, event);
	}

	//NEWGAME
	if (buttons.at("NEW_GAME")->getState() == BTN_PRESSED)
	{
		this->states->push(new SelectionCharacter(this->window, this->supportedKeys, this->states));
		return;
	}

	if (buttons.at("EXIT")->getState() == BTN_PRESSED)
	{
		this->states->top()->endState();
	}
}

void MainMenuState::update(const sf::Time& delta_time)
{
	this->updateInput(delta_time.asSeconds());
}

void MainMenuState::update(const sf::Time & delta_time, sf::Event event)
{
	updateMousePos();
	updateButtons(event);
}

void MainMenuState::render(std::shared_ptr<sf::RenderWindow> target)
{
	if (!target)
		target = this->window;
	target->draw(background);
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->draw(target);
	}
	//render del player
}
