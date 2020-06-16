#ifndef BUTTON_H
#define  BUTTON_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <string>

#include "MovementComponent.h"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

class Button
{
public:
	Button() {};
	Button(const std::string& path, const std::string& string, sf::Color color, float character_size, sf::Vector2f txtpos,
		sf::Vector2f size, sf::Color outline_color, float thickness, sf::Color fill_color, sf::Vector2f boxpos, const sf::Texture& txt = sf::Texture(), sf::Vector2f scale = sf::Vector2f(1, 1));
	~Button();

	void setText(const std::string& path, const std::string& string, sf::Color color, float character_size, sf::Vector2f pos);
	void setBox(sf::Vector2f size, sf::Color color, float thickness, sf::Color fill_color, sf::Vector2f pos, sf::Texture* txt = NULL, sf::Vector2f scale = sf::Vector2f(1, 1));

	void setPosition(sf::Vector2f pos);
	void setScale(sf::Vector2f scale);

	void setStandard();

	button_states getState();
	sf::RectangleShape getBox();

	void draw(std::shared_ptr<sf::RenderWindow> target);

	void update(const sf::Vector2f mouse_pos_view);
	void update(const sf::Vector2f mouse_pos_view, sf::Event event);
	void buttonAnimation(sf::Color newcolor);
	void buttonAnimation();

private:
	//Functions
	bool isHover(sf::Vector2f mouse_pos_view);
	void isActive(sf::Vector2f mouse_pos_view, sf::Event event);
	void isActive(sf::Vector2f mouse_pos_view);

	//Variables
	short unsigned buttonstate;
	sf::Font font;
	sf::Text text;

	sf::RectangleShape box;

	sf::Vector2f original_pos;
	sf::Vector2f right_scale;
	sf::Color right_color;
};

#endif // !BUTTON_H