#include "TileSheetAnimator.h"
#include <iostream>


TileSheetAnimator::TileSheetAnimator(sf::Vector2u dim, sf::Vector2u imagecount, sf::Vector2u startimage, float switchtime, int totimages)
{
	this->_linecount = imagecount;
	this->_switchtime = switchtime;
	this->_startimage = startimage;
	_totaltime = 0.f;
	_currentimage = _startimage;
	_totalimages = totimages;
	_uvrect.left = startimage.x;
	_uvrect.top = startimage.y;
	_uvrect.width = dim.x / imagecount.x;
	_uvrect.height = dim.y / imagecount.y;

	_active = false;
	_resetted = false;
}

TileSheetAnimator::TileSheetAnimator()
{
}

TileSheetAnimator::~TileSheetAnimator()
{
}

sf::IntRect TileSheetAnimator::update(const sf::Time & deltatime, int row)
{
	if (!_active)
		_active = true;
	if (_resetted)
		_resetted = false;

	if (row != 0)
		_currentimage.y = row;

	_totaltime += deltatime.asSeconds();
	if (_totaltime >= _switchtime)
	{
		_totaltime = 0;
		_currentimage.x++;
		if (_totalimages != 0)
		{
			if (_currentimage.x >= _linecount.x)
			{
				_currentimage.x = _startimage.x;
				_currentimage.y++;
				if (_currentimage.y >= _linecount.y)
					_currentimage = _startimage;
			}
			_imagecounter++;
			if (_imagecounter > _totalimages - 1)
			{
				_currentimage = _startimage;
				_imagecounter = 0;
			}
			
		}
		else if (_currentimage.x >= _linecount.x)
		{
			_currentimage.x = _startimage.x;
			_currentimage.y++;
			if (_currentimage.y >= _linecount.y)
				_currentimage = _startimage;
		}
	}
	_uvrect.left = _currentimage.x * _uvrect.width;
	_uvrect.top = _currentimage.y * _uvrect.height;
	return _uvrect;
}

void TileSheetAnimator::setRect(sf::IntRect rect)
{
	this->_uvrect = rect;
}

const sf::IntRect & TileSheetAnimator::getRect()
{
	return this->_uvrect;
}

void TileSheetAnimator::setSwitchTime(float time)
{
	this->_switchtime = time;
}

void TileSheetAnimator::reset()
{
	_active = false;
	_resetted = true;
	_imagecounter = 0;
	_currentimage = _startimage;
	_totaltime = 0.f;
}

bool TileSheetAnimator::isResetted()
{
	return _resetted;
}

bool TileSheetAnimator::isActive()
{
	return _active;
}

bool TileSheetAnimator::isEndAnimation()
{
	return (_currentimage == _linecount);
}
