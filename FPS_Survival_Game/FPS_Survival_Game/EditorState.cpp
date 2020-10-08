#include "EditorState.h"
#include <string>

//Initializer functions
void EditorState::initVariables()
{
	//NEWMAP
	newmap = false;
	//SAVED
	saved = false;
	//TEXTS
	editor.setFont(title_font);
	editor.setCharacterSize(80);
	editor.setPosition(sf::Vector2f(0, 820));
	editor.setString("EDITOR");
	editor.setFillColor(sf::Color::Green);
	
	positions.setFont(text_font);
	positions.setCharacterSize(22);
	positions.setPosition(sf::Vector2f(mouse_pos_view.x - 100, mouse_pos_view.y + 50));
	std::string pos = std::to_string(mouse_pos_view.x) + " - " + std::to_string(mouse_pos_view.y);
	positions.setString(pos);
	positions.setFillColor(sf::Color::Green);

	comands.setFont(text_font);
	comands.setCharacterSize(24);
	comands.setString(
		"COMANDS: W = move up; - S = move down; \n			A = move left; - D = move right; \n			Q = zoom in; - E = zoom out; \n			Mouse Left = select/add tile; - Mouse Right = clear;");
	comands.setPosition(this->window->getSize().x - comands.getGlobalBounds().width - 10, 820.f);
	comands.setFillColor(sf::Color::White);

	//TILESET
	this->textures->load(Textures::Tileset, "Sources/tileSheet/EditorTileset.png");
	tileset_texture = this->textures->get(Textures::Tileset);
	tileset.setTexture(&tileset_texture);
	tileset.setSize(sf::Vector2f((float)(this->textures->get(Textures::Tileset).getSize().x), (float)(this->textures->get(Textures::Tileset).getSize().y)));
	tileset.setPosition(sf::Vector2f(0, 952));

	//VIEW
	cameraSpeed = 800.f;
	view.setViewport(sf::FloatRect(0, 0, 1, 0.75));	
	view.setSize(sf::Vector2f(window->getSize().x * view.getViewport().width, window->getSize().y * view.getViewport().height));
	view.setCenter(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
	
	//SELECTOR
	selector.setSize(sf::Vector2f(64.f, 64.f));
	selector.setPosition(mouse_pos_view);
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::White);

	//CAMERA
	camera.setSize(sf::Vector2f(1920.f, 1088.f));
	camera.setOutlineThickness(3.f);
	camera.setOutlineColor(sf::Color::Green);
	camera.setFillColor(sf::Color::Transparent);
	camera.setPosition(sf::Vector2f(view.getCenter().x - view.getSize().x/2, view.getCenter().y - view.getSize().y/2));

	//MAP
	this->textures->load(Textures::MainMenuState, "Sources/background.jpg");
	map_texture = this->textures->get(Textures::MainMenuState);
	map.setTexture(&map_texture);
	map.setPosition(sf::Vector2f(view.getViewport().left, view.getViewport().top));
	map.setSize(sf::Vector2f((float)(map_texture.getSize().x), (float)(map_texture.getSize().y)));

	//TILESET GRID
	sf::Vector2f sel_size = sf::Vector2f(selector.getSize());
	tileset_grid.resize(17, std::vector<std::shared_ptr<Tile>>());
	for (auto i = 0; i < tileset_grid.size(); i++)
	{
		tileset_grid[i].resize(30);
		for (auto j = 0; j < tileset_grid[i].size(); j++)
		{
			tileset_grid[i][j] = std::make_shared<Tile>();
			tileset_grid[i][j]->getShape()->setPosition(sf::Vector2f(j * sel_size.x, i * sel_size.y));
			tileset_grid[i][j]->getShape()->setSize(selector.getSize());
			tileset_grid[i][j]->getShape()->setOutlineThickness(0.5f);
			tileset_grid[i][j]->getShape()->setOutlineColor(sf::Color::Transparent);
			tileset_grid[i][j]->getShape()->setFillColor(sf::Color::Transparent);
		}
	}
}

void EditorState::initFonts()
{
	if (!this->title_font.loadFromFile("Fonts/04B_30__.TTF"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT 04B_30__.TTF FONT");
	}
	if (!this->text_font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD PixellettersFull.ttf FONT");
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void EditorState::initButtons()
{
	this->buttons["LOAD"] = std::make_unique<Button>
		("Fonts/PixellettersFull.ttf", "Load", sf::Color::Magenta, 36.f, 
			sf::Vector2f(editor.getPosition().x + editor.getGlobalBounds().width + 300, editor.getPosition().y),
			sf::Vector2f(80, 28), sf::Color::Magenta, 1.f, sf::Color::Transparent,
			sf::Vector2f(editor.getPosition().x + editor.getGlobalBounds().width + 300, editor.getPosition().y + 15));

	this->buttons["NEW MAP"] = std::make_unique<Button>
		("Fonts/PixellettersFull.ttf", "New Map", sf::Color::Magenta, 36.f,
			sf::Vector2f(buttons["LOAD"]->getBox().getPosition().x + buttons["LOAD"]->getBox().getGlobalBounds().width + 50, editor.getPosition().y),
			sf::Vector2f(120, 28), sf::Color::Magenta, 1.f, sf::Color::Transparent,
			sf::Vector2f(buttons["LOAD"]->getBox().getPosition().x + buttons["LOAD"]->getBox().getGlobalBounds().width + 50, editor.getPosition().y + 15));
	
	this->buttons["SAVE"] = std::make_unique<Button>
		("Fonts/PixellettersFull.ttf", "Save", sf::Color::Magenta, 36.f,
			sf::Vector2f(buttons["NEW MAP"]->getBox().getPosition().x + buttons["NEW MAP"]->getBox().getGlobalBounds().width + 50, editor.getPosition().y),
			sf::Vector2f(80, 28), sf::Color::Magenta, 1.f, sf::Color::Transparent,
			sf::Vector2f(buttons["NEW MAP"]->getBox().getPosition().x + buttons["NEW MAP"]->getBox().getGlobalBounds().width + 50, editor.getPosition().y + 15));

}

EditorState::EditorState(std::shared_ptr<sf::RenderWindow> window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->textures = std::make_shared<TextureHolder>();
	this->initFonts();
	this->initVariables();
	this->initKeybinds();
	this->initButtons();
}

EditorState::~EditorState()
{
}

//Functions
void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) )
	{
		window->setView(this->window->getDefaultView());
		this->states->top()->endState();
	}
}

void EditorState::updateEditorInput(const sf::Time& dt)
{
	//MAP.txt
	if (newmap == false)
	{
		std::ifstream file;
		file.open("C:/Users/Federico/source/Repos/FPS_Survival_Game/FPS_Survival_Game/FPS_Survival_Game/Sources/NewMap.txt");
		if (file)
		{
			newmap = true;
			saved = true;
		}
		else
		{
			newmap = false;
			saved = true;
		}
		file.close();
	}

	//Move view
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		view.move(0.f, -this->cameraSpeed * dt.asSeconds());
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		view.move(0.f, this->cameraSpeed * dt.asSeconds());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		view.move(-this->cameraSpeed * dt.asSeconds(), 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		view.move(this->cameraSpeed * dt.asSeconds(), 0.f);
	}

	//ZOOM
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ZOOM_OUT_CAMERA"))))
		view.zoom(0.99f);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("ZOOM_IN_CAMERA"))))
		view.zoom(1.01f);

	//SELECTOR
	sf::Vector2f mouse_pos = sf::Vector2f(sf::Mouse::getPosition(*this->window).x, sf::Mouse::getPosition(*this->window).y);
	sf::Vector2f mouse_posV = sf::Vector2f(window->mapPixelToCoords(sf::Vector2i(mouse_pos.x, mouse_pos.y), view));
	selector.setPosition(sf::Vector2f(mouse_posV.x - (selector.getGlobalBounds().width / 2), mouse_posV.y - (selector.getGlobalBounds().height / 2)));
	if (newmap)
	{
		if (mouse_pos_view.y > (1080.f - tileset.getSize().y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			selector.setTexture(&this->textures->get(Textures::Tileset));
			selector.setTextureRect(sf::IntRect((int)((tileset.getPosition().x + mouse_pos_view.x) / 64) * 64,
				(int)((mouse_pos_view.y - tileset.getPosition().y) / 64) * 64, (int)(selector.getSize().x), (int)(selector.getSize().y)));
		}
		else
		{
			//reset the color to show texture or behind the selector in case we have a texture or not
			if (selector.getTexture() == NULL)
				selector.setFillColor(sf::Color::Transparent);
			else
				selector.setFillColor(sf::Color::White);
		}

		if (mouse_posV.y < 1080.f && mouse_posV.y > 0 &&
			mouse_posV.x > 0.f && mouse_posV.x < 1920.f)
		{
			sf::Vector2i map_pos = sf::Vector2i(mouse_posV.x / 64, mouse_posV.y / 64);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && selector.getTexture() != NULL)
			{
				//reset color in order to display the texture
				tileset_grid[map_pos.y][map_pos.x]->getShape()->setFillColor(sf::Color::White);
				tileset_grid[map_pos.y][map_pos.x]->getShape()->setTexture(&this->textures->get(Textures::Tileset));
				tileset_grid[map_pos.y][map_pos.x]->getShape()->setTextureRect(selector.getTextureRect());
				tileset_grid[map_pos.y][map_pos.x]->calculateType(selector.getTextureRect().left, selector.getTextureRect().top, selector.getSize().x);
				if (saved)
					saved = false;
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && tileset_grid[map_pos.y][map_pos.x]->getShape()->getTexture() != NULL)
			{
				tileset_grid[map_pos.y][map_pos.x]->getShape()->setFillColor(sf::Color::Transparent);
				tileset_grid[map_pos.y][map_pos.x]->getShape()->setTexture(NULL);
				tileset_grid[map_pos.y][map_pos.x]->getShape()->setTextureRect(sf::IntRect());
				tileset_grid[map_pos.y][map_pos.x]->setType(-1);
				if (saved)
					saved = false;
			}
		}
	}
	//POS
	std::string pos = std::to_string(mouse_posV.x ) + " -- " + std::to_string(mouse_posV.y);
	positions.setString(pos);
	positions.setPosition(sf::Vector2f(mouse_pos.x - 100, mouse_pos.y + 50));
}

void EditorState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionlaity.*/

	for (auto &it : this->buttons)
	{
		it.second->update(this->mouse_pos_view);
	}

	if (buttons.at("NEW MAP")->getState() == BTN_PRESSED && !newmap)
	{
		MyFile = std::ofstream("Sources/NewMap.txt");
		if (MyFile.is_open())
		{
			for (int i = 0; i < tileset_grid.size(); i++)
			{
				for (int j = 0; j < tileset_grid[i].size(); j++)
				{
					MyFile << "-1[" + std::to_string(j) + "-" + std::to_string(i) + "], ";
					tileset_grid[i][j]->setType(-1);
				}
				MyFile << "\n";
			}
		}
		newmap = true;
		MyFile.close();
	}
	if (buttons.at("LOAD")->getState() == BTN_PRESSED && newmap)
	{
		std::ifstream file;

		file.open("Sources/NewMap.txt");
		while (file.is_open())
		{
			while (!file.eof())
			{
				auto i = 0;
				while (i < tileset_grid.size())
				{
					std::string str, value;
					std::getline(file, str);
					std::stringstream stream(str);
					auto j = 0;
					while (j < tileset_grid[i].size())
					{
						while (std::getline(stream, value, ' ') && file.peek() != '\n')
						{
							std::string t_type = value.substr(0, value.find(','));
							int tile_type = atoi(t_type.c_str());

							this->tileset_grid[i][j] = std::make_shared<Tile>(j * 64.f, i * 64.f, 64.f, tileset_texture, tile_type);
							if (tile_type == -1)
							{
								this->tileset_grid[i][j]->getShape()->setFillColor(sf::Color::Transparent);
							}
							j++;
						}
					}
					i++;
				}
			}
			file.close();
		}
	}
	if (buttons.at("SAVE")->getState() == BTN_PRESSED && !saved)
	{
		std::ofstream file;
		file.open("Sources/NewMap.txt");
		int i = 0;
		while (i < tileset_grid.size())
		{
			int j = 0;
			while (j < tileset_grid[i].size())
			{
				file << std::to_string(tileset_grid[i][j]->getType());
				file << "[" + std::to_string(j) + "-" + std::to_string(i) + "], ";
				j++;
			}
			file << "\n";
			i++;
		}
		file.close();
		saved = true;
	}
}

void EditorState::createMap()
{
}

void EditorState::update(const sf::Time& dt)
{
	this->updateMousePos();
	this->updateInput(dt.asSeconds());

	this->updateButtons();
	this->updateEditorInput(dt);
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto &it : this->buttons)
	{
		it.second->draw(this->window);
	}
}

void EditorState::render(std::shared_ptr<sf::RenderWindow> target)
{
	if (!target)
		target = this->window;

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target);
	window->draw(tileset);
	window->draw(editor);
	window->draw(comands);
	
	target->setView(this->view);
	//window->draw(map);
	window->draw(camera);
	for (int i = 0; i < tileset_grid.size(); i++)
		for (int j = 0; j < tileset_grid[i].size(); j++)
			tileset_grid[i][j]->render(target);
	if (mouse_pos_view.y < 810.f)
		window->draw(selector);
	else
	{
		target->setView(this->window->getDefaultView());
		selector.setSize(sf::Vector2f(64.f, 64.f));
		selector.setPosition(sf::Vector2f(mouse_pos_view.x - (selector.getGlobalBounds().width / 2),
			mouse_pos_view.y - (selector.getGlobalBounds().height / 2)));
		window->draw(selector);
	}

	target->setView(this->window->getDefaultView());
	window->draw(positions);

}