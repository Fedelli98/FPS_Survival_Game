#include "Game.h"

//Static functions

//Initializer functions

void Game::initVariables()
{
	this->window = NULL;
	this->fullscreen = false;
}

void Game::initWindow()
{
	/*Creates a SFML window.*/
	std::ifstream ifs("Config/window.ini");
	this->videomodes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode windowbounds = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	unsigned framelimit = 120;
	bool verticalsyncenenabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> windowbounds.width >> windowbounds.height;
		ifs >> fullscreen >> windowbounds.height;
		ifs >> framelimit;
		ifs >> verticalsyncenenabled;
		ifs >> antialiasing_level;
	}

	ifs.close();

	this->windowsettings.antialiasingLevel = antialiasing_level;
	if (fullscreen)
		this->window = std::make_shared<sf::RenderWindow>(windowbounds, title, sf::Style::Fullscreen, windowsettings);
	else
		this->window = std::make_shared<sf::RenderWindow>(windowbounds, title, sf::Style::Titlebar | sf::Style::Close, windowsettings);

	this->window->setFramerateLimit(framelimit);
	this->window->setVerticalSyncEnabled(verticalsyncenenabled);
}


void Game::initKeys()
{
	std::fstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;
		}
	}

	ifs.close();


	for (auto i : this->supportedKeys)
	{
		std::cout << i.first << " " << i.second << std::endl;
	}
}

void Game::initStates()
{
	this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}

void Game::updateMenu(const sf::Time& timeperframe, sf::Event event)
{
	this->states.top()->update(timeperframe, event);

	if (this->states.top()->getQuit())
	{
		this->states.top()->endState();
		delete this->states.top();
		this->states.pop();
	}
}

void Game::updateGame(const sf::Time & timeperframe)
{
	this->states.top()->update(timeperframe);

	if (this->states.top()->getQuit())
	{
		this->states.top()->endState();
		delete this->states.top();
		this->states.pop();
	}
}

//Constructors/Destructors
Game::Game()
{
	this->initWindow();
	this->initKeys();
	this->initStates();
}

Game::~Game()
{	
	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//Functions

void Game::endApplication()
{

}

void Game::updateDt()
{
	/*Updates the dt variable with the time it takes to update and render one frame.*/

	this->dt = this->dtClock.restart();
}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	GameStates::Type prev_state = this->states.top()->getID();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			if (this->states.top()->getID() == GameStates::Menu)
			{
				if (prev_state != GameStates::Menu)
					prev_state = GameStates::Menu;
				sf::Event Event;
				while (this->window->pollEvent(Event) &&
					this->states.top()->getID() == GameStates::Menu &&
					!this->states.empty())
				{
					updateMenu(dt, Event);
				}
				updateDt();
			}
			else
				if (this->states.top()->getID() == GameStates::Game)
				{
					if (prev_state == GameStates::Menu)
					{
						updateDt();
						prev_state = GameStates::Game;
					}
					else
						updateGame(dt);
				}
		}
	}
	else
	{
		this->endApplication();
		window->close();
	}
}

void Game::render()
{
	this->window->clear();  
	
	//Render items
	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::run()
{
	sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Clock clock;

	while (this->window->isOpen())
	{
		{
			//processEvents();
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				/*processEvents();*/
				if (!this->states.empty())
				{
					GameStates::Type prev_state = this->states.top()->getID();
					if (this->window->hasFocus())
					{
						if (this->states.top()->getID() == GameStates::Menu)
						{
							if (prev_state != GameStates::Menu)
								prev_state = GameStates::Menu;
							sf::Event Event;
							while (this->window->pollEvent(Event) &&
								this->states.top()->getID() == GameStates::Menu &&
								!this->states.empty())
							{
								updateMenu(TimePerFrame, Event);
							}
							clock.restart();
						}
						else
							if (this->states.top()->getID() == GameStates::Game)
							{
								if (prev_state == GameStates::Menu)
								{
									clock.restart();
									prev_state = GameStates::Game;
								}
								else
									updateGame(TimePerFrame);
							}
					}
				}
				else
					window->close();
				render();
			}
		}
	}
}