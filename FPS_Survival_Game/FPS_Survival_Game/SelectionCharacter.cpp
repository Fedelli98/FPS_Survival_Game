#include "SelectionCharacter.h"
#include "StShotgunPlayerFight.h"
#include "StRiflePlayerFight.h"
#include "StGunPlayerFight.h"

SelectionCharacter::SelectionCharacter(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->ID = GameStates::Menu;
	initBackground();
	initTextures();
	initButtons();
}

void SelectionCharacter::update(const sf::Time& delta_time, sf::Event event)
{
	window->setView(window->getDefaultView());
	updateMousePos();
	updateButtons(event);
}

void SelectionCharacter::render(std::shared_ptr<sf::RenderWindow> target)
{
	window->draw(background);
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->draw(target);
	}
}

void SelectionCharacter::initButtons()
{
	//SHOTGUN
	this->buttons["SHOTGUN"] = std::make_unique<Button>
		("Fonts/edunline.ttf", "", sf::Color::Transparent, 0, sf::Vector2f(0.f, 0.f),
			sf::Vector2f((float)this->textures->get(Textures::ShotgunP).getSize().x,
			(float)this->textures->get(Textures::ShotgunP).getSize().y),
			sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(350.f, 320.f), textures->get(Textures::ShotgunP));
	//RIFLE
	this->buttons["RIFLE"] = std::make_unique<Button>
		("Fonts/edunline.ttf", "", sf::Color::Transparent, 0, sf::Vector2f(0.f, 0.f),
			sf::Vector2f((float)this->textures->get(Textures::RifleP).getSize().x,
			(float)this->textures->get(Textures::RifleP).getSize().y),
			sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(800.f, 320.f), textures->get(Textures::RifleP));
	//GUN
	this->buttons["HANDGUN"] = std::make_unique<Button>
		("Fonts/edunline.ttf", "", sf::Color::Transparent, 0, sf::Vector2f(0.f, 0.f),
			sf::Vector2f((float)this->textures->get(Textures::HandgunP).getSize().x,
			(float)this->textures->get(Textures::HandgunP).getSize().y),
			sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(1250.f, 320.f), textures->get(Textures::HandgunP));
	//RETURN
	this->buttons["RETURN"] = std::make_unique<Button>
		("Fonts/edunline.ttf", "Exit Game", sf::Color::Black, 70.f, sf::Vector2f(725.f, 930.f),
			sf::Vector2f(350.f, 50.f), sf::Color::Transparent, 0.f, sf::Color::Transparent, sf::Vector2f(725.f, 955.f));
}

void SelectionCharacter::initBackground()
{
	background_txt.loadFromFile("Sources/background.jpg");
	background.setTexture(background_txt);
}

void SelectionCharacter::initTextures()
{
	this->textures = std::make_shared<TextureHolder>();
	textures->load(Textures::ShotgunP, "Sources/Top_Down_Survivor/shotgun/move/survivor-move_shotgun_0.png");
	textures->load(Textures::RifleP, "Sources/Top_Down_Survivor/rifle/move/survivor-move_rifle_0.png");
	textures->load(Textures::HandgunP, "Sources/Top_Down_Survivor/handgun/move/survivor-move_handgun_0.png");
}

void SelectionCharacter::updateButtons(sf::Event event)
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		it->second->update(mouse_pos_view, event);
	}

	//SHOTGUN
	if (buttons.at("SHOTGUN")->getState() == BTN_HOVER && buttons.at("SHOTGUN")->getPrevState() == BTN_PRESSED)
	{
		this->states->push(new GameState(calcMapSize(), this->window, this->supportedKeys, this->states, Textures::ID::ShotgunP, std::make_shared<StShotgunPlayerFight>(StShotgunPlayerFight())));
		return;
	}

	//RIFLE
	else if (buttons.at("RIFLE")->getState() == BTN_HOVER && buttons.at("RIFLE")->getPrevState() == BTN_PRESSED)
	{
		this->states->push(new GameState(calcMapSize(), this->window, this->supportedKeys, this->states, Textures::ID::RifleP, std::make_shared<StRiflePlayerFight>(StRiflePlayerFight())));
		return;
	}

	//HANDGUN
	else if (buttons.at("HANDGUN")->getState() == BTN_HOVER && buttons.at("HANDGUN")->getPrevState() == BTN_PRESSED)
	{
		this->states->push(new GameState(calcMapSize(), this->window, this->supportedKeys, this->states, Textures::ID::HandgunP, std::make_shared<StGunPlayerFight>(StGunPlayerFight())));
		return;
	}

	//EXIT_GAME
	if (buttons.at("RETURN")->getState() == BTN_PRESSED)
	{
		this->states->top()->endState();
	}

}

sf::Vector2i SelectionCharacter::calcMapSize()
{
	sf::Vector2i mapsize;

	std::string mapname = "Sources/NewMap.txt";
	std::ifstream openfile(mapname);
	if (!openfile.is_open())
	{
		mapname = "Sources/Mappa.txt";
		openfile.open(mapname);
	}

	std::string str1, value1;
	std::getline(openfile, str1);
	std::stringstream stream1(str1);
	while (std::getline(stream1, value1, ' ') && openfile.peek() != '\n')
	{
		mapsize.x += 1;
	}
	while (!openfile.eof())
	{
		std::string str1, value1;
		std::getline(openfile, str1);
		std::stringstream stream1(str1);
		while (std::getline(stream1, value1, '\n') && openfile.peek() != '\n')
			mapsize.y += 1;
	}
	mapsize.y += 1;
	openfile.close();

	return mapsize;
}
