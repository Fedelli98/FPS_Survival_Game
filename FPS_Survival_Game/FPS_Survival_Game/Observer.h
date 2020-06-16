#pragma once
class Observer
{
public:
	Observer() = default;
	virtual ~Observer() = default;

	virtual void update() = 0;

	virtual void attach() = 0;
	virtual void detach() = 0;
};

