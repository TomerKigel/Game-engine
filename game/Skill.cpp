#include "Skill.h"
#include "Player.h"
#include "Monster.h"
#include "Movable.h"
#include <memory>
#include <iostream>

void Skill::Move(double xspd, double yspd)
{
	SetTL(double(GetTL().GetX() + xspd), double(GetTL().GetY() + yspd));
	SetBR(double(GetBR().GetX() + xspd), double(GetBR().GetY() + yspd));
}

Skill::Skill(AABB range, double cooldown, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt, std::shared_ptr<Object> o)
{
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr)
	{
		sf::Vector2f siz(range.GetWid(), range.GetLen());
		mdisp = std::make_shared<Graphics>(cor, siz, window);
	}
	else
	{
		AABB *t = new AABB(0,0,33,50);
		mdisp = std::make_shared<Graphics>(cor, txt, window, t);
	}
	setAABB(range);
	refreshLastSpace();
	owner = o;
	skilltype = melee;
	cd.SetTimerMaxAsSeconds(cooldown);
	animantioncooldown.SetTimerMaxAsSeconds(0.025);
	timetolive.SetTimerMaxAsSeconds(0.1);
}

void Skill::isTimeToDie()
{
	if (timetolive.IsTimeUp())
		destroy();
}

bool Skill::intersection(AABB *ab)
{
	Object* obj = static_cast<Object*>(ab);
	switch (obj->reType())
	{
	case ply:
		{
			if (this->owner->reType() == mnstr) {
				destroy();
			}
		break;

		}
	case sttc:
		{
			if (skilltype == ranged) {
				destroy();
			}
			break;
		}
	case mnstr:
		{
			if (this->owner->reType() == ply)
				if (skilltype == ranged)
				{
					destroy();
				}
			break;
		}
	}
	return true;
}

void Skill::draw()
{
		refreshLastSpace();
		sf::Vector2f p(GetTL().GetX(), GetTL().GetY());
		refreshgraphics(p);
		if (animantioncooldown.IsTimeUp()) {
			mdisp->switchToNextFrame();
			animantioncooldown.resetTimer();
		}
		mdisp->Draw();
}

short Skill::reType()
{
	return skill;
}

void Skill::refreshgraphics(sf::Vector2f pos)
{
	mdisp->refreshPosition(pos);
}

void Skill::action()
{
	UpdateMO();
	isTimeToDie();
}

void Skill::UpdatePRTO()
{
	short direction = 0;
	AABB *ab = nullptr;
	switch (owner->reType())
	{
		case mnstr:
		{
			std::shared_ptr<Monster> t = std::dynamic_pointer_cast<Monster>(owner);
			ab = t->getAABB();
			direction = t->mnstrstate.looking_state;
			break;
		}
		case ply:
		{
			std::shared_ptr<Player> m = std::dynamic_pointer_cast<Player>(owner);
			ab = m->getAABB();
			direction = m->reState().looking_state;
			break;
		}
	}
	//AABB *ab = dynamic_cast<Movable*>(owner)->getSpace();

	if (direction == lookingleft)
	{
		if (mdisp->reDir() == left) {
			mdisp->FlipHorizontali();
		}
		Move(ab->GetTL().GetX() - GetBR().GetX(), ab->GetBR().GetY() - GetBR().GetY());
	}
	else if (direction == lookingright)
	{
		if (mdisp->reDir() == right) {
			mdisp->FlipHorizontali();
		}
		Move(ab->GetBR().GetX() - GetTL().GetX(), ab->GetBR().GetY() - GetBR().GetY());
	}
}

void Skill::UpdateRanged()
{
}

void Skill::UpdateMO()
{
	if (skilltype == melee)
		UpdatePRTO();
	else if (skilltype == ranged)
		UpdateRanged();
}

std::shared_ptr<Object> Skill::returnowner()
{
	return owner;
}

Skill::~Skill()
{
	cd.~Cooldown();
	timetolive.~Cooldown();
}
