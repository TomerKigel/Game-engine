#include "Intersections.h"
#include "Movable.h"
#include "Monster.h"
#include "Player.h"
#include "StaticObject.h"
#include "Item.h"
#include "Skill.h"
#include "Mat.h"

void Activatintrsct(AABB *a, AABB *b)
{
	int ttypea = 0, ttypeb = 0;
	if ((*a -= *b) > 0)
	{
		ttypea = a->ownerptr->reType();
		ttypeb = b->ownerptr->reType();

		if (ttypea == ply)
		{
			dynamic_cast<Player*>(a->ownerptr)->intersection(b->ownerptr);
			if (ttypeb == sttc) 
			{
				dynamic_cast<StaticObject*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == mnstr)
			{
				dynamic_cast<Monster*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == itm)
			{
				dynamic_cast<Item*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == skill)
			{
				dynamic_cast<Skill*>(b->ownerptr)->intersection(a->ownerptr);
			}
		}
		if (ttypea == mnstr)
		{
			dynamic_cast<Monster*>(a->ownerptr)->intersection(b->ownerptr);
			if (ttypeb == sttc)
			{
				dynamic_cast<StaticObject*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == ply)
			{
				dynamic_cast<Player*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == skill)
			{
				dynamic_cast<Skill*>(b->ownerptr)->intersection(a->ownerptr);
			}
		}
		if (ttypea == itm)
		{
			dynamic_cast<Item*>(a->ownerptr)->intersection(b->ownerptr);
			if (ttypeb == sttc)
			{
				dynamic_cast<StaticObject*>(b->ownerptr)->intersection(a->ownerptr);
			}
			if (ttypeb == ply)
			{
				dynamic_cast<Player*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == skill)
			{
				dynamic_cast<Skill*>(b->ownerptr)->intersection(a->ownerptr);
			}
		}
		if (ttypea == sttc)
		{
			dynamic_cast<StaticObject*>(a->ownerptr)->intersection(b->ownerptr);
			if (ttypeb == ply)
			{
				dynamic_cast<Player*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == mnstr)
			{
				dynamic_cast<Monster*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == itm)
			{
				dynamic_cast<Item*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == skill)
			{
				dynamic_cast<Skill*>(b->ownerptr)->intersection(a->ownerptr);
			}
		}
		if (ttypea == skill)
		{
			dynamic_cast<Skill*>(a->ownerptr)->intersection(b->ownerptr);
			if (ttypeb == ply)
			{
				dynamic_cast<Player*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == mnstr)
			{
				dynamic_cast<Monster*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == itm)
			{
				dynamic_cast<Item*>(b->ownerptr)->intersection(a->ownerptr);
			}
			else if (ttypeb == sttc)
			{
				dynamic_cast<StaticObject*>(b->ownerptr)->intersection(a->ownerptr);
			}
		}
	}
}