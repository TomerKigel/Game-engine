#include "Movable.h"
#include <memory>
//
//Moveable::Moveable(AABB range)
//{
//	space = range;
//}
//
//Moveable::Moveable(Point tl, Point br)
//{
//	space = AABB(tl,br);
//}
//
//Moveable::Moveable(double tlx, double tly, double brx, double bry)
//{
//	space = AABB(tlx,tly,brx,bry);
//}
//
//void Moveable::Move(double xspd, double yspd)
//{
//	space.SetTL(space.GetTL().GetX()+xspd, space.GetTL().GetY() + yspd);
//	space.SetBR(space.GetBR().GetX() + xspd, space.GetBR().GetY() + yspd);
//}

AABB *Movable::getSpace()
{
	return &space;
}

AABB *Movable::getLastSpace()
{
	return &Lastspace;

}

void Movable::SpaceBack()
{
	space = Lastspace;
}

void Movable::refreshLastSpace()
{
	Lastspace = space;
}

short Movable::reType()
{
	return mveble; 
}

void Movable::PhysicsInit()
{
	setToMove(ph.calcSpeed());
}

void Movable::Accelerate(double x, double y)
{
	ph.AccelerateX(x);
	ph.AccelerateY(y);
}

void Movable::setToMove(PhysicsStats ph)
{
	Move(ph.xspeed, ph.yspeed);
}

void Movable::PhysicsIntersection(short direction, double overlap)
{
	if (direction == top)
	{
		Move(0,-overlap);
		ph.intersection(0, 1,top);
	}
	if (direction == bottom)
	{
		Move(0,overlap);
		ph.intersection(0, 1,bottom);
	}
	if (direction == left)
	{
		Move(-overlap,0);
		ph.intersection(1, 0,left);
	}
	if (direction == right)
	{
		Move(overlap, 0);
		ph.intersection(1, 0,right);
	}
}