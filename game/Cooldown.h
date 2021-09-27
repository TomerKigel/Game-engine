#pragma once
#include <SFML/Graphics.hpp>

class Cooldown
{
private:
	sf::Clock clk;
	double clkMaxLim;
public:
	////////////////////////////////////////////////////////////////////////////////////////
	//Default constructor			
	//
	//\brief   sets timer to a limit of 1 second
	//
	//\param clkMaxLim  max timer as 1 second
	////////////////////////////////////////////////////////////////////////////////////////
	Cooldown() { clkMaxLim = 1; }
	////////////////////////////////////////////////////////////////////////////////////////
	//constructor			
	//
	//\brief   sets max limit to timer
	//
	//\param seconds   max timer as seconds	
	////////////////////////////////////////////////////////////////////////////////////////
	Cooldown(double seconds);
	////////////////////////////////////////////////////////////////////////////////////////
	//Accessor		
	//
	//\brief   sets and chnages timer limit as seconds
	//
	//\param seconds   max timer as seconds	
	////////////////////////////////////////////////////////////////////////////////////////
	void SetTimerMaxAsSeconds(double seconds);
	////////////////////////////////////////////////////////////////////////////////////////
	//Accessor			
	//
	//\brief   increases the timer max limit by seconds
	//
	//\param seconds   increase max timer as seconds	
	////////////////////////////////////////////////////////////////////////////////////////
	void IncTimerBySeconds(double seconds);
	////////////////////////////////////////////////////////////////////////////////////////
	//Accessor			
	//
	//\brief   decreases the timer max limit by seconds
	//
	//\param seconds   decrease max timer as seconds	
	////////////////////////////////////////////////////////////////////////////////////////
	void DecTimerBySeconds(double seconds);
	////////////////////////////////////////////////////////////////////////////////////////
	//Boolean test			
	//
	//\brief   Tests if time is up returns true is time is up flase if not
	//
	////////////////////////////////////////////////////////////////////////////////////////
	bool IsTimeUp();
	////////////////////////////////////////////////////////////////////////////////////////
	//Accessor			
	//
	//\brief   resets timer to 0
	////////////////////////////////////////////////////////////////////////////////////////
	const void resetTimer();

	////////////////////////////////////////////////////////////////////////////////////////
	//Accessor			
	//
	//\brief   returns the current counted time by parameter clk
	////////////////////////////////////////////////////////////////////////////////////////
	const double reTime();

	////////////////////////////////////////////////////////////////////////////////////////
	//Accessor			
	//
	//\brief   returns the current Max time limit
	////////////////////////////////////////////////////////////////////////////////////////
	const double reMaxTime();

	////////////////////////////////////////////////////////////////////////////////////////
	//Default destructor			
	////////////////////////////////////////////////////////////////////////////////////////
	~Cooldown();
};