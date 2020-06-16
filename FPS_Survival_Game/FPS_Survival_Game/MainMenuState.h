#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "SelectionCharacter.h"

class MainMenuState : 
	public State
{
private:
	//Variables
	sf::RectangleShape background;
	std::map<std::string, std::unique_ptr<Button>> buttons;
	//Funtions
	void initKeybinds();
	void initBackground();
	void initButtons();
	void initTextures();

public:
	MainMenuState(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();
	//Functions

	void updateInput(const float& dt);
	void updateButtons(sf::Event event);
	void update(const sf::Time& delta_time);
	virtual void update(const sf::Time& delta_time, sf::Event event);
	void render(std::shared_ptr<sf::RenderWindow> target = nullptr);
};

#endif.	