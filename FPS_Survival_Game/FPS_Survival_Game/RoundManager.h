#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Subject.h"

class RoundManager : public Subject
{
public:
	RoundManager();
	virtual ~RoundManager();

	virtual void subscribe(Observer* obs);
	virtual void unsubscribe(Observer* obs);

	virtual void notify();


	void startCountdown(const sf::Time& delta_time);

	void increaseRound();
	void increaseKills();
	void increaseBoss();

	void reset();

	bool isBossRound();
	bool isLoading();

	sf::Time getCountdown();
	int      getCounterRound();
	int      getCounterBoss();

	void     setBossRound(bool boolean);
	void     setKills(int kills);

	int getKills();
	int getTotalKills();
	int getKillsPerRound();
	int getRoundPerBoss();

private:
	sf::Time countdown;
	bool loading;

	int kill_counter;
	int total_kills;
	int boss_counter;

	const int kills_per_round = 1;
	const int round_per_boss = 4;

	int counter_round;
	bool boss;

	std::list<Observer *> observers;
};

