#include "Animation.h"

Animation::Animation(const sf::Texture& texture, Textures::OBJECTS id, sf::Vector2f position, float timer,
	sf::Vector2u dim, sf::Vector2u imagecount, float switchtime, sf::Vector2f scale, sf::Vector2u startimage) :
	TileSheetAnimator(dim, imagecount, startimage, switchtime)
{
	this->timer = timer;

	this->id = id;
	this->rect.left = _uvrect.left;
	this->rect.top = _uvrect.top;
	this->rect.width = _uvrect.width;
	this->rect.height = _uvrect.height;

	this->shape.setPosition(sf::Vector2f(position.x/* - _uvrect.width/2*/, position.y/* - _uvrect.height/2*/));
	this->shape.setSize(sf::Vector2f(float(_uvrect.width), float(_uvrect.height)));
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(rect);
	this->shape.setScale(scale);
}

Animation::~Animation()
{
}

float Animation::getTimer()
{
	return this->timer;
}

sf::RectangleShape Animation::getShape()
{
	return this->shape;
}

Textures::OBJECTS Animation::getId()
{
	return id;
}

void Animation::setShapeTxtRect(sf::IntRect shape)
{
	this->shape.setTextureRect(shape);
}

void Animation::updateTimer(const sf::Time& delta_time)
{
	this->timer -= delta_time.asSeconds();
}

void Animation::render(std::shared_ptr<sf::RenderWindow> target)
{
	target->draw(shape);
}
