#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

namespace Textures
{
	enum ID { Personaggio, PersonaggioMS, ShotgunP, RifleP, HandgunP, Enemy, Proiettile, Boss, Pet };
	enum SHOOT { Rilfe_S, Handgun_S, Shotgun_S, Enemy_Attack };
	enum BACKGROUND { MainMenuState };
	enum OBJECTS { HP, MS, Blood, Coin, Settings, Tileset, Esc};
}



class TextureHolder   //NO COSTRU PERCHE MAP VUOTA
{
public:
	
	void load(Textures::ID id, const std::string& filename);
	void load(Textures::SHOOT id, const std::string& filename);
	void load(Textures::ID id, std::unique_ptr<sf::Texture> texture);
	void load(Textures::BACKGROUND id, const std::string& filename);
	void load(Textures::OBJECTS id, const std::string& filename);


	const sf::Texture& get(Textures::ID id) const;
	const sf::Texture& get(Textures::SHOOT id) const;
	const sf::Texture& get(Textures::BACKGROUND id) const;
	const sf::Texture& get(Textures::OBJECTS id) const;


private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> texture_map;
	std::map<Textures::SHOOT, std::unique_ptr<sf::Texture>> texture_map_shoot;
	std::map<Textures::BACKGROUND, std::unique_ptr<sf::Texture>> texture_map_background;
	std::map<Textures::OBJECTS, std::unique_ptr<sf::Texture>> texture_map_objects;

};

