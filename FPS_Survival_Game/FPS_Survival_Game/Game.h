#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//Variables
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videomodes;
	sf::ContextSettings windowsettings;
	bool fullscreen;

	sf::Clock dtClock;
	sf::Time dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariables();
	void initWindow();
	void initKeys();
	void initStates();

	void updateMenu(const sf::Time& timeperframe, sf::Event event);
	void updateGame(const sf::Time& timeperframe);


public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

#endif