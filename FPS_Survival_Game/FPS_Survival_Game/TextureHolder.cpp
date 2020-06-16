#include "TextureHolder.h"
#include <assert.h>

void TextureHolder::load(Textures::ID id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
	{//THROW ERROR
		throw std::runtime_error("il file" + filename + "errore");

		auto inserted = texture_map.insert(std::make_pair(id, std::move(texture)));
	}

	texture->loadFromFile(filename);

	texture_map.insert(std::make_pair(id, std::move(texture)));
}

void TextureHolder::load(Textures::SHOOT id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
	{//THROW ERROR
		throw std::runtime_error("il file" + filename + "errore");

		auto inserted = texture_map_shoot.insert(std::make_pair(id, std::move(texture)));
	}

	texture->loadFromFile(filename);

	texture_map_shoot.insert(std::make_pair(id, std::move(texture)));
}

void TextureHolder::load(Textures::ID id, std::unique_ptr<sf::Texture> texture)
{
	texture_map.insert(std::make_pair(id, std::move(texture)));
}

void TextureHolder::load(Textures::BACKGROUND id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
	{//THROW ERROR
		throw std::runtime_error("il file" + filename + "errore");

		auto inserted = texture_map_background.insert(std::make_pair(id, std::move(texture)));
	}

	texture->loadFromFile(filename);

	texture_map_background.insert(std::make_pair(id, std::move(texture)));
}

void TextureHolder::load(Textures::OBJECTS id, const std::string & filename)
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());
	if (!texture->loadFromFile(filename))
	{//THROW ERROR
		throw std::runtime_error("il file" + filename + "errore");

		auto inserted = texture_map_objects.insert(std::make_pair(id, std::move(texture)));
	}

	texture->loadFromFile(filename);

	texture_map_objects.insert(std::make_pair(id, std::move(texture)));
}

const sf::Texture & TextureHolder::get(Textures::ID id) const
{
	auto found = texture_map.find(id);

	return *found->second;
}

const sf::Texture & TextureHolder::get(Textures::SHOOT id) const
{
	auto found = texture_map_shoot.find(id);

	return *found->second;
}

const sf::Texture & TextureHolder::get(Textures::BACKGROUND id) const
{
	auto found = texture_map_background.find(id);

	return *found->second;
}

const sf::Texture & TextureHolder::get(Textures::OBJECTS id) const
{
	auto found = texture_map_objects.find(id);

	return *found->second;
}
