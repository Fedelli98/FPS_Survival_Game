#include "RoundManager.h"



RoundManager::RoundManager()
{
	countdown = sf::seconds(6.f);
	loading = true;
	boss = false;
	counter_round = 1;
	kill_counter = 0;
	boss_counter = 0;
}


RoundManager::~RoundManager()
{
}

void RoundManager::subscribe(Observer* obs)
{
	this->observers.push_back(obs);
}

void RoundManager::unsubscribe(Observer* obs)
{
	this->observers.remove(obs);
}

void RoundManager::notify()
{
	for (auto itr = std::begin(observers); itr != std::end(observers); itr++)
	{
		(*itr)->update();
	}
}

void RoundManager::increaseRound()
{
	this->counter_round++;
	notify();
}

void RoundManager::increaseKills()
{
	this->kill_counter++;
	this->total_kills++;

	notify();
}

void RoundManager::increaseBoss()
{
	this->boss_counter++;
	notify();
}

void RoundManager::reset()
{
	loading = true;
	countdown = sf::seconds(6.f);
}

void RoundManager::startCountdown(const sf::Time& delta_time)
{
	countdown -= delta_time;
	if (countdown <= sf::seconds(1.f))
		loading = false;
}

bool RoundManager::isBossRound()
{
	return 
		this->boss;
}

sf::Time RoundManager::getCountdown()
{
	return this->countdown;
}

bool RoundManager::isLoading()
{
	return this->loading;
}

int RoundManager::getCounterRound()
{
	return
		this->counter_round;
}

int RoundManager::getCounterBoss()
{
	return
		this->boss_counter;
}

void RoundManager::setBossRound(bool boolean)
{
	this->boss = boolean;
}

void RoundManager::setKills(int kills)
{
	this->kill_counter = kills;
}

int RoundManager::getKills()
{
	return
		this->kill_counter;
}

int RoundManager::getTotalKills()
{
	return
		this->total_kills;
}

int RoundManager::getKillsPerRound()
{
	return
		this->kills_per_round;
}

int RoundManager::getRoundPerBoss()
{
	return
		this->round_per_boss;
}
