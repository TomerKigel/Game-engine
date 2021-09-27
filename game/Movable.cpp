#include "Movable.h"
#include <memory>

AABB *Movable::getLastSpace()
{
	return &Lastspace;

}

void Movable::SpaceBack()
{
	setAABB(Lastspace);
}

void Movable::refreshLastSpace()
{
	Lastspace = *getAABB();
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
