#pragma once
#include <SFML/Graphics.hpp>
class TileSheetAnimator
{
public:
	TileSheetAnimator(sf::Vector2u dim, sf::Vector2u imagecount, sf::Vector2u startimage, float switchtime, int totimages = 0);
	TileSheetAnimator();
	~TileSheetAnimator();

	sf::IntRect update(const sf::Time& deltatime, int row = 0);

	void setRect(sf::IntRect rect);
	const sf::IntRect& getRect();

	void setSwitchTime(float time);

	void reset();
	bool isResetted();
	bool isActive();
	bool isEndAnimation();

protected:
	sf::IntRect _uvrect;
	sf::Vector2u _linecount;
	sf::Vector2u _currentimage;
	sf::Vector2u _startimage;

	float _totaltime;
	int _totalimages;
	int _imagecounter;
	float _switchtime;

	bool _active;
	bool _resetted;
};

