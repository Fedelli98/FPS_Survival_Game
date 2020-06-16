#include "Button.h"

Button::Button(const std::string& path, const std::string& string, sf::Color color, float character_size,
	sf::Vector2f txtpos, sf::Vector2f size, sf::Color outline_color, float thickness, const sf::Color fill_color,
	const sf::Vector2f boxpos, const sf::Texture& txt, sf::Vector2f scale)
{
	//TEXT
	this->buttonstate = BTN_IDLE;
	this->font.loadFromFile(path);
	this->text.setFont(this->font);
	this->text.setString(string);
	this->text.setFillColor(color);
	this->text.setCharacterSize(static_cast<unsigned int>(character_size));
	this->text.setPosition(txtpos);

	//original_pos = pos;
	right_scale.x = this->text.getScale().x,
		right_scale.y = this->text.getScale().y;
	right_color = this->text.getFillColor();

	//BOX
	this->box.setSize(size);
	this->box.setScale(scale);
	this->box.setOutlineColor(outline_color);
	this->box.setOutlineThickness(thickness);
	if (txt.getSize() != sf::Vector2u(0, 0))
	{
		this->box.setTexture(&txt);
		this->box.setOrigin(sf::Vector2f(box.getSize().x / 2.f, box.getSize().y / 2.f));
		this->box.setPosition(box.getOrigin() - sf::Vector2f(box.getGlobalBounds().width / 2.f, box.getGlobalBounds().height / 2.f) + boxpos);
	}
	else
	{
		this->box.setPosition(boxpos);
		this->box.setFillColor(fill_color);
	}
	original_pos = box.getPosition();
	if (text.getScale() != sf::Vector2f())
	{
		this->right_scale = this->box.getScale();
	}
}

Button::~Button()
{
}

void Button::setText(const std::string& path, const std::string& string, sf::Color color, float character_size, sf::Vector2f pos)
{
	this->font.loadFromFile(path);
	this->text.setFont(this->font);
	this->text.setString(string);
	this->text.setFillColor(color);
	this->text.setCharacterSize(static_cast<unsigned int>(character_size));
	this->text.setPosition(pos);

	//original_pos = pos;
	right_scale.x = this->text.getScale().x,
		right_scale.y = this->text.getScale().y;
	right_color = this->text.getFillColor();
}

void Button::setBox(sf::Vector2f size, sf::Color outline_color, float thickness, const sf::Color fill_color, const sf::Vector2f pos, sf::Texture* txt, sf::Vector2f scale)
{
	this->box.setSize(size);
	this->box.setScale(scale);
	this->box.setOutlineColor(outline_color);
	this->box.setOutlineThickness(thickness);
	if (txt == NULL)
		this->box.setFillColor(fill_color);
	this->box.setPosition(pos);
	this->box.setTexture(txt);

	original_pos = pos;
	if (text.getScale() != sf::Vector2f())
	{
		this->right_scale = this->box.getScale();
	}
}

void Button::setPosition(sf::Vector2f pos)
{
	this->box.setPosition(pos);
}

void Button::setScale(sf::Vector2f scale)
{
	this->box.setScale(scale);
}

button_states Button::getState()
{
	return button_states(this->buttonstate);
}

sf::RectangleShape Button::getBox()
{
	return this->box;
}

bool Button::isHover(const sf::Vector2f mouse_pos_view)
{
	if (box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouse_pos_view)))
		return true;
	else
		return false;
}

void Button::isActive(const sf::Vector2f mouse_pos_view, sf::Event event)
{
	if (isHover(mouse_pos_view))
	{
		this->buttonstate = BTN_HOVER;
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (buttonstate != BTN_PRESSED)
					this->buttonstate = BTN_PRESSED;
			}
		}
	}
}

void Button::isActive(sf::Vector2f mouse_pos_view)
{
	if (isHover(mouse_pos_view))
	{
		this->buttonstate = BTN_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (buttonstate != BTN_PRESSED)
			{
				this->buttonstate = BTN_PRESSED;
			}
		}
	}
}

void Button::update(const sf::Vector2f mouse_pos_view)
{
	this->buttonstate = BTN_IDLE;

	isActive(mouse_pos_view);


	switch (this->buttonstate)
	{
	case BTN_IDLE:
		setStandard();
		break;

	case BTN_HOVER:
		if (text.getCharacterSize() > 1)
			buttonAnimation(sf::Color::White);
		break;

	case BTN_PRESSED:
		if (text.getCharacterSize() > 1)
			buttonAnimation(sf::Color::White);
		else
			buttonAnimation();
		break;

	default:
		setStandard();
		break;
	}
}

void Button::update(const sf::Vector2f mouse_pos_view, sf::Event event)
{
	this->buttonstate = BTN_IDLE;

	isActive(mouse_pos_view, event);


	switch (this->buttonstate)
	{
	case BTN_IDLE:
		setStandard();
		break;

	case BTN_HOVER:
		if (text.getCharacterSize() > 1)
			buttonAnimation(sf::Color::White);
		else 
			setStandard();
		break;

	case BTN_PRESSED:
		if (text.getCharacterSize() > 1)
			buttonAnimation(sf::Color::White);
		else
			buttonAnimation();
		break;

	default:
		setStandard();
		break;
	}
}


void Button::buttonAnimation(sf::Color newcolor)
{
	if (right_color == this->text.getFillColor() || right_scale == this->text.getScale())
	{
		text.setScale(text.getScale().x * 1.1f, text.getScale().y * 1.1f);
		text.setFillColor(newcolor);
	}
}

void Button::buttonAnimation()
{
 	sf::Vector2f pos = sf::Vector2f(box.getPosition() +
		sf::Vector2f(box.getSize().x / 2, box.getSize().y / 2));
	box.setScale(box.getScale() - sf::Vector2f(0.2f, 0.2f));
	//box.setPosition(pos);
}

void Button::setStandard()
{
	text.setScale(right_scale);
	text.setFillColor(right_color);
	//text.setPosition(original_pos);
	box.setScale(right_scale);
	box.setPosition(original_pos);

	//box.setFillColor(right_color);
}


void Button::draw(std::shared_ptr<sf::RenderWindow> target)
{
	target->draw(this->box);
	target->draw(this->text);
}
