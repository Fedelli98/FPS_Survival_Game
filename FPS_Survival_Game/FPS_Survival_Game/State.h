#ifndef STATE_H
#define STATE_H

#include "Entity.h"
#include "TextureHolder.h"
#include "Button.h"
#include <SFML/Window.hpp>

namespace GameStates
{
	enum Type { Game, Menu };
}

class State
{
private:
	bool quit;

	bool allanimdone;

protected:
	//Varaibles
	std::map<std::string, std::unique_ptr<Button>> buttons;

	std::stack<State*>* states;

	std::shared_ptr<sf::RenderWindow> window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;  

	//Resources
	std::shared_ptr<TextureHolder> textures;
	sf::Vector2f mouse_pos_view;

	GameStates::Type ID;
	//Funtions
	virtual void initKeybinds() = 0;

public:

	State() {};
	State(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Funcions
	const bool& getQuit();
	GameStates::Type getID();

	void updateMousePos();
	
	void endState();
	virtual bool endAnimation();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const sf::Time& delta_time) = 0;
	virtual void update(const sf::Time& delta_time, sf::Event event) = 0;

	virtual void render(std::shared_ptr<sf::RenderWindow> target = NULL) = 0;
};

#endif