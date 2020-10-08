#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "Button.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include <iostream>
#include <fstream>

class EditorState :
	public State
{
private:
	//Variables
	sf::View view;
	float cameraSpeed;

	sf::Font title_font;
	sf::Font text_font;
	sf::Text editor;
	sf::Text positions;
	sf::Text comands;

	std::ofstream MyFile;
	bool newmap;
	bool saved;
	sf::Texture map_texture;
	sf::RectangleShape map;
	sf::Texture tileset_texture;
	sf::RectangleShape tileset;
	std::vector<std::vector<std::shared_ptr<Tile>>> tileset_grid;
	
	sf::RectangleShape camera;

	sf::RectangleShape selector;
	sf::Sprite selector2;


	//Functions
	void initVariables();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	EditorState(std::shared_ptr<sf::RenderWindow> window, 
		std::map<std::string, int>* supportedKeys, 
		std::stack<State*>* states);
	virtual ~EditorState();

	//Functions
	void updateInput(const float& dt);
	void updateEditorInput(const sf::Time& dt);
	void updateButtons();
	void createMap();
	void update(const sf::Time& dt);
	void update(const sf::Time& dt, sf::Event event) {};
	void renderButtons(sf::RenderTarget& target);
	void render(std::shared_ptr<sf::RenderWindow> target);
};

#endif
