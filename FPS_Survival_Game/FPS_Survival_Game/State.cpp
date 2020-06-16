#include "State.h"

State::State(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	this->quit = false;
}

State::~State()
{
}

const bool & State::getQuit()
{
	return this->quit;
}

GameStates::Type State::getID()
{
	return this->ID;
}

void State::updateMousePos()
{
	this->mouse_pos_view = (window)->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::endState()
{
	this->quit = true;
}
