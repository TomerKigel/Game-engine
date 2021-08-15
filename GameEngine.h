#pragma once
#include "Sound.h"
#include "Graphics.h"
#include "Player.h"
#include <fstream>
#include <iterator>

class GameEngine
{
private:
	bool isPaused;
	bool GameOver = false;
	std::shared_ptr<Sound> s;
	std::shared_ptr<sf::RenderWindow> window;
	std::shared_ptr<sf::Texture> me;
	std::shared_ptr<Graphics> menu;
	std::shared_ptr<sf::Texture> gome;
	std::shared_ptr<Graphics> gomenu;
	sf::Event event;
	sf::Sound theme;
	std::shared_ptr<Player> plyr;

	void EventLoop();
public:
	GameEngine(char *filename = nullptr);
	void GameLoop();
	void Musicfilestream(std::string filename);
	void Graphicsfilestream(std::string filename);
	void LoadFromFile(std::string filename);
	~GameEngine();
};