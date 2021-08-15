#include "Item.h"
#include "Mat.h"
#include "StaticObject.h"

Item::Item(AABB range, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt)
{
	space = range;
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr)
	{
		sf::Vector2f siz(range.GetLen(), range.GetWid());
		mdisp = std::make_shared<Graphics>(cor, siz, window);
	}
	else
	{
		mdisp = std::make_shared<Graphics>(cor, txt, window,&space);
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
	space.SetOwner(this);
}

void Item::draw()
{
	refreshLastSpace();
	sf::Vector2f p(space.GetTL().GetX(), space.GetTL().GetY());
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


void Item::intersection(Object *obj)
{
	switch (obj->reType())
	{
	case ply:
		destroy();
		break;
	case sttc:
		AABB *t = this->getSpace();
		short dir = 0;
		double overlap = 0;
		StaticObject *sptr = dynamic_cast<StaticObject*>(obj);
		dir = Lastspace.WIRTTO(*sptr->getSpace());
		overlap = getSpace()->Overlap(*sptr->getSpace(), dir);
		PhysicsIntersection(dir, overlap);
		break;
	}
}

void Item::Move(double xspd, double yspd)
{
	space.SetTL(double(space.GetTL().GetX() + xspd), double(space.GetTL().GetY() + yspd));
	space.SetBR(double(space.GetBR().GetX() + xspd), double(space.GetBR().GetY() + yspd));
}