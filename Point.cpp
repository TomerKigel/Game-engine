#include "Point.h"

//Default constructor
//Point::Point() {}

Point::Point(double Xcor, double Ycor)
{
	X = Xcor;
	Y = Ycor;
}

Point::Point(Point &p)
{
	X = p.GetX();
	Y = p.GetY();
}

void Point::operator=(Point &p)
{
	X = p.GetX();
	Y = p.GetY();
}

bool Point::operator==(Point &pnt)
{
	if (X == pnt.GetX() && Y == pnt.GetY())
		return true;
	return false;

}

double Point::GetX()
{
	return X;
}

double Point::GetY()
{
	return Y;
}

void Point::SetX(double nx)
{
	X = nx;
}

void Point::SetY(double ny)
{
	Y = ny;
}

//Default Destructor
//Point::~Point() {}