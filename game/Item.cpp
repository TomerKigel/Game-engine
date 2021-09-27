#include "Item.h"
#include "Mat.h"
#include "StaticObject.h"

Item::Item(AABB range, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt)
{
	setAABB(range);
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr)
	{
		sf::Vector2f siz(range.GetLen(), range.GetWid());
		mdisp = std::make_shared<Graphics>(cor, siz, window);
	}
	else
	{
		mdisp = std::make_shared<Graphics>(cor, txt, window,getAABB());
	}
	refreshLastSpace();
	PhysicsStats pps;
	pps.topspeed = 5;
	pps.accx = 0;
	pps.accy = 0;
	pps.topacc = 1;
	pps.xspeed = 0;
	pps.yspeed = -10;
	ph.setObjectsParameters(pps);
	animantioncooldown.SetTimerMaxAsSeconds(0.1);
}

void Item::draw()
{
	refreshLastSpace();
	sf::Vector2f p((*getAABB()).GetTL().GetX(), (*getAABB()).GetTL().GetY());
	refreshgraphics(p);
	if (animantioncooldown.IsTimeUp()) {
		mdisp->switchToNextFrame();
		animantioncooldown.resetTimer();
	}
	mdisp->Draw();
}


short Item::reType()
{
	return itm;
}

void Item::refreshgraphics(sf::Vector2f pos)
{
	mdisp->refreshPosition(pos);
}


Item::~Item()
{
}


bool Item::intersection(AABB *ab)
{
	Object* obj = static_cast<Object*>(ab);
	switch (obj->reType())
	{
	case ply:
		destroy();
		break;
	case sttc:
		short dir = 0;
		double overlap = 0;
		StaticObject *sptr = dynamic_cast<StaticObject*>(obj);
		dir = Lastspace.WIRTTO(*sptr->getAABB());
		overlap = getAABB()->Overlap(*sptr->getAABB(), dir);
		PhysicsIntersection(dir, overlap);
		break;
	}
	return true;
}

void Item::action()
{
	PhysicsInit();
}

void Item::Move(double xspd, double yspd)
{
	SetTL(double(GetTL().GetX() + xspd), double(GetTL().GetY() + yspd));
	SetBR(double(GetBR().GetX() + xspd), double(GetBR().GetY() + yspd));
}
