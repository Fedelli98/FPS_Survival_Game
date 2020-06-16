#pragma once
#include "Observer.h"

class Subject
{
public:
	Subject() = default;
	virtual ~Subject() = default;

	virtual void subscribe(Observer* obs) = 0;
	virtual void unsubscribe(Observer* obs) = 0;

	virtual void notify() = 0;
};

