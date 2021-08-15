#pragma comment(lib, "steam_api")
#include "GameEngine.h"
#include "steam_api.h"
#include <iostream>


int main()
{
	/*if (SteamAPI_RestartAppIfNecessary(480))
	{
		//return true;
	}

	try
	{
		if (!SteamAPI_Init())
			throw(1);
	}
	catch(int e)
	{
		std::cout << "Error number:'" << e << "': SteamApi Failed to load";
	}
	try
	{
		if (!SteamUserStats()->RequestCurrentStats())
			throw(2);
	}
	catch (int e)
	{
		std::cout << "Error number:'" << e << "': Steam failed retrieving your stats";
	}
	bool *isachivment = nullptr;
	try{
		if (!SteamUserStats()->GetAchievement("First_Login", isachivment))
			throw(3);
		if (*isachivment == false)
			SteamUserStats()->SetAchievement("First_Login");
	}
	catch (int e)
	{
		std::cout << "Error number:'" << e << "': No achievement found";
	}*/
	GameEngine game;
	game.GameLoop();
	//SteamAPI_Shutdown();
}
