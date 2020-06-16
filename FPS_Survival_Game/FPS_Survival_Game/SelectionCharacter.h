#pragma once
#include "State.h"
#include "Button.h"
#include "GameState.h"

class SelectionCharacter :
	public State
{
public:
	SelectionCharacter(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SelectionCharacter() = default;

private:
	//Functions
	virtual void updateInput(const float& dt) {};
	virtual void update(const sf::Time& delta_time, sf::Event event) override;
	virtual void update(const sf::Time& delta_time) {};
	virtual void render(std::shared_ptr<sf::RenderWindow> target = nullptr);

	virtual void initKeybinds() {};
	void initButtons();
	void initBackground();
	void initTextures();
	void updateButtons(sf::Event event);

	//Variables

	sf::Sprite background;
	sf::Texture background_txt;

};