#pragma once
#include "Monster.h"
#include "Skill.h"

class Bat : public Monster
{
private:
	double ohight;
	Cooldown attTimer;
public:
	Bat(double opthight,double tspd, AABB range, double hp, double ad, double spd, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt);
	void Controls();
	bool intersection(AABB *obj);
	short reMType();
	short reType();
	~Bat() {}
};
