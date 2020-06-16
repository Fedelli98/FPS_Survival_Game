#pragma once
#include "State.h"
#include "Button.h"

class PauseMenu :
	public State
{
public:
	PauseMenu(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~PauseMenu();

private:

	virtual void update(const sf::Time& delta_time, sf::Event event) override;
	virtual void update(const sf::Time& delta_time);
	virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);

	void initButtons();
	void initBackground();

	void updateButtons(sf::Event event);

	virtual void initKeybinds();
	virtual void updateInput(const float& dt);
	//Variables

	sf::Texture background_txt;
	sf::Sprite background;
};

