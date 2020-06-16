#include "PauseMenu.h"

PauseMenu::PauseMenu(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->ID = GameStates::Menu;
	initBackground();
	initButtons();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::update(const sf::Time& delta_time, sf::Event event)
{
	window->setView(window->getDefaultView());
	updateMousePos();
	updateButtons(event);
	//render();
}

void PauseMenu::update(const sf::Time& delta_time)
{
	throw std::runtime_error("Unexpected error");
	return;
}

void PauseMenu::render(std::shared_ptr<sf::RenderWindow> target)
{
	target->draw(background);
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->draw(target);
	}
}

void PauseMenu::initBackground()
{
	background_txt.loadFromFile("Sources/background.jpg");
	background.setTexture(background_txt);
}

void PauseMenu::updateButtons(sf::Event event)
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->update(mouse_pos_view, event);
	}

	//RESUME
	if (buttons.at("RESUME")->getState() == BTN_PRESSED)
	{
		this->states->top()->endState();
		return;
	}

	//MAIN MENU
	if (buttons.at("MAIN_MENU")->getState() == BTN_PRESSED)
	{
		this->states->pop();
		this->states->pop();
		this->states->top()->endState();
	}

	//EXIT_GAME
	if (buttons.at("EXIT")->getState() == BTN_PRESSED)
	{
		//Check if it works or if it's better to code window->close()
		this->states->pop();
		this->states->pop();
		this->states->pop();
		this->states->top()->endState();
	}
}

void PauseMenu::initKeybinds()
{
}

void PauseMenu::updateInput(const float & dt)
{
}

void PauseMenu::initButtons()
{
	//RESUME
	this->buttons["RESUME"] = std::make_unique<Button>
		("Sources/edunline.ttf", "RESUME", sf::Color::Black, 100.f, sf::Vector2f(650.f, 200.f),
			sf::Vector2f(355, 75.f), sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(650.f, 230.f));
	//MAIN_MENU
	this->buttons["MAIN_MENU"] = std::make_unique<Button>
		("Sources/edunline.ttf", "Main Menu", sf::Color::Black, 100.f, sf::Vector2f(770.f, 400.f),
			sf::Vector2f(510, 75.f), sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(770.f, 430.f));
	//EXIT
	this->buttons["EXIT"] = std::make_unique<Button>
		("Sources/edunline.ttf", "Exit Game", sf::Color::Black, 70.f, sf::Vector2f(890.f, 600.f),
			sf::Vector2f(355.f, 50.f), sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(890.f, 620.f));
}
