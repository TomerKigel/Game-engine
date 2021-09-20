#pragma once

#include "SFML\Graphics.hpp"
#include "AABB.h"
typedef struct
{
	sf::Texture tbuf;
	std::string name;
}tbuffer;

static class Textures
{
private:
	std::vector<tbuffer>ListOfTextures;

public:
	Textures() {}

	void SetTexturesBuffer(std::string filename);

	sf::Texture *getTexture(std::string filename);

	std::vector<tbuffer>* reTbuf();

	~Textures() {}
};