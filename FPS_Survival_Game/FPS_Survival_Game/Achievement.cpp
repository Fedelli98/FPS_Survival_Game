#include "Achievement.h"



Achievement::Achievement(RoundManager * subject)
{
	this->subject = subject;
	this->round = 0;
	this->kills = 0;
	this->kills_boss = 0;

	this->clock_kills = 1.5f;
	this->clock_round = 1.5f;
	this->clock_boss = 1.5f;


	//TESTO
	this->font.loadFromFile("Sources/04B_30__.ttf");
	this->text.setFont(this->font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(15);

	//KILLS
	this->kills_t.setFont(this->font);
	this->kills_t.setFillColor(sf::Color::White);
	this->kills_t.setCharacterSize(30);

	//ROUND
	this->round_t.setFont(this->font);
	this->round_t.setFillColor(sf::Color::White);
	this->round_t.setCharacterSize(30);

	//BOSS
	this->kills_boss_t.setFont(this->font);
	this->kills_boss_t.setFillColor(sf::Color::White);
	this->kills_boss_t.setCharacterSize(30);

	attach();
}


Achievement::~Achievement()
{
	detach();
}

void Achievement::update()
{//update e' per ogni kill
	//ROUND
	if (this->round != this->subject->getCounterRound() - 1)
	{
		this->round = this->subject->getCounterRound() - 1;
		if (this->round == 1 || (this->round + 1) % 5 == 0)
		{
			this->round_on = true;
			this->round_drawing = this->round;
		}
	}

	//KILLS
	this->kills = this->subject->getTotalKills();
	if (this->kills == 1 || ((this->kills) % 15 == 0) && this->kills != 0)
	{
		this->kills_on = true;
		this->kills_drawing = this->kills;
	}

	//BOSS
	if (this->kills_boss != this->subject->getCounterBoss())
	{
		this->kills_boss = this->subject->getCounterBoss();
		if (this->kills_boss == 1 || (this->kills_boss + 1) % 3 == 0)
		{
			this->boss_on = true;
			this->kills_boss_drawing = this->kills_boss;
		}
	}
}

void Achievement::attach()
{
	this->subject->subscribe(this);
}

void Achievement::detach()
{
	this->subject->unsubscribe(this);
}

bool Achievement::isRoundOn()
{
	return this->round_on;
}

bool Achievement::isKillsOn()
{
	return this->kills_on;
}

bool Achievement::isBossOn()
{
	return this->boss_on;
}

void Achievement::updateBadge(const sf::Time& delta_time)
{
	if (this->kills_on)
		this->clock_kills -= delta_time.asSeconds();

	if (this->round_on)
		this->clock_round -= delta_time.asSeconds();

	if (this->boss_on)
		this->clock_boss -= delta_time.asSeconds();
}

void Achievement::renderRoundBadge(std::shared_ptr<sf::RenderWindow> window, const sf::View& view)
{
	if (this->clock_round > 0)
	{
		this->text.setString("New Achievement ROUND :");
		this->text.setPosition(view.getCenter().x - 150, view.getCenter().y - 300);

		this->round_t.setString(std::to_string(round_drawing +1));
		this->round_t.setPosition(view.getCenter().x + 145, view.getCenter().y - 315);

		window->draw(this->text);
		window->draw(this->round_t);
	}
	else
	{
		this->clock_round = 1.5f;
		this->round_on = false;
	}
}

void Achievement::renderKillsBadge(std::shared_ptr<sf::RenderWindow> window, const sf::View& view)
{
	if (this->clock_kills > 0)
	{
		this->text.setString("New Achievement KILLS :");
		this->text.setPosition(view.getCenter().x - 150, view.getCenter().y - 330);

		this->kills_t.setString(std::to_string(kills_drawing));
		this->kills_t.setPosition(view.getCenter().x + 140, view.getCenter().y - 345);

		window->draw(this->text);
		window->draw(this->kills_t);
	}
	else
	{
		this->clock_kills = 1.5f;
		this->kills_on = false;
	}
}

void Achievement::renderBossBadge(std::shared_ptr<sf::RenderWindow> window, const sf::View& view)
{
	if (this->clock_boss > 0)
	{
		this->text.setString("New Achievement BOSS :");
		this->text.setPosition(view.getCenter().x - 150, view.getCenter().y - 270);

		this->kills_boss_t.setString(std::to_string(kills_boss_drawing));
		this->kills_boss_t.setPosition(view.getCenter().x + 145, view.getCenter().y - 285);

		window->draw(this->text);
		window->draw(this->kills_boss_t);
	}
	else
	{
		this->clock_boss = 1.5f;
		this->boss_on = false;
	}
}
