#pragma comment(lib, "steam_api")
#include "GameEngine.h"
#include "steam_api.h"
#include <iostream>


int main()
{
	GameEngine game;
	game.GameLoop();
}
