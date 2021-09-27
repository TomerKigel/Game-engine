#include "AABB.h"
#include "Mat.h"
#define PI 3.14159265

AABB::AABB(double tlx, double tly, double brx, double bry)
{
	TL = Point(tlx,tly);
	BR = Point(brx, bry);
}


AABB::AABB(Point tl, Point br)
{
	TL = tl;
	BR = br;

}

Point AABB::GetCenter()
{
	Point Center;
	Center.SetX((TL.GetX() + BR.GetX()) / 2);
	Center.SetY((TL.GetY() + BR.GetY()) / 2);
	return Center;
}

int AABB::GetLen()
{
	return (BR.GetX() - TL.GetX());
}


int AABB::GetWid()
{
	return (BR.GetY() - TL.GetY());
}

Point AABB::GetTL()
{
	return TL;
}

Point AABB::GetBR()
{
	return BR;
}

bool AABB::operator==(AABB &range)
{
	if (  !(BR.GetX() < range.TL.GetX() || range.BR.GetX() < TL.GetX()) &&
		  !(BR.GetY() < range.TL.GetY() || range.BR.GetY() < TL.GetY())   )
		{
				return true;
		}
	return false;
}

int AABB::operator-=(AABB &range)
{
	if ( (range.GetTL().GetX() - BR.GetX() == 1 || TL.GetX() - range.GetBR().GetX() == 1) && (TL.GetY() <= range.BR.GetY() && BR.GetY() >= range.TL.GetY()))
	{
		if ((range.GetTL().GetY() - BR.GetY() == 1 || TL.GetY() - range.GetBR().GetY() == 1) && (TL.GetX() <= range.BR.GetX() && BR.GetX() >= range.TL.GetX()))
			return 3;
		return 1;
	}
	if ((range.GetTL().GetY() - BR.GetY() == 1 || TL.GetY() - range.GetBR().GetY() == 1) && (TL.GetX() <= range.BR.GetX() && BR.GetX() >= range.TL.GetX()))
	{
		return 2;
	}
	if(*getAABB() == range)
	{
		return 4;
	}
	return false;
}

bool AABB::isContaining(Point pnt)
{
	if ((pnt.GetX() >= TL.GetX() && pnt.GetX() <= BR.GetX()) &&
		(pnt.GetY() >= TL.GetY() && pnt.GetY() <= BR.GetY()))
	{
			return true;
	}
	return false;
}

void AABB::operator=(AABB &origin)
{
	TL.SetX(origin.TL.GetX());
	TL.SetY(origin.TL.GetY());
	BR.SetX(origin.BR.GetX());
	BR.SetY(origin.BR.GetY());
}

void AABB::setAABB(AABB &origin)
{
	TL.SetX(origin.TL.GetX());
	TL.SetY(origin.TL.GetY());
	BR.SetX(origin.BR.GetX());
	BR.SetY(origin.BR.GetY());
}


void AABB::operator*=(double f)
{
	Point ttl = TL;
	TL.SetX(TL.GetX() - ((BR.GetX() - TL.GetX()) / (f / 2)));
	TL.SetY(TL.GetY() - ((BR.GetY() - TL.GetY()) / (f / 2)));
	BR.SetX(BR.GetX() + ((BR.GetX() - ttl.GetX()) / (f / 2)));
	BR.SetY(BR.GetY() + ((BR.GetY() - ttl.GetY()) / (f / 2)));
}


void AABB::SetTL(double x, double y)
{
	TL.SetX(x);
	TL.SetY(y);
}
void AABB::SetBR(double x, double y)
{
	BR.SetX(x);
	BR.SetY(y);
}

//void AABB::SetOwner(Object *ptr)
//{
//	ownerptr = ptr;
//}

AABB *AABB::getAABB()
{
	return this;
}

short AABB::WIRTTO(AABB t) //where in relation to this object
{
	/*double x = t.getAABB()->GetCenter().GetX();
	double y = t.getAABB()->GetCenter().GetY();
	double lastX = getAABB()->GetCenter().GetX();
	double lastY = getAABB()->GetCenter().GetY();

	x = x - lastX;
	y = y - lastY;
	if (abs(x) > t.getAABB()->GetLen()) {
		if (x > 0)
			return right;
		else
			return left;
	}
	else {
		if (y > 0)
			return top;
		else
			return bottom;
	}*/
	double tl = t.GetLen();
	double tw = t.GetWid();
	double deg = 0;
	if (tl >= tw) {
		deg = 90 - (atan(tw / tl)* 180.0 / PI);
		
		tl = GetCenter().GetX() - t.GetCenter().GetX();
		tw = GetCenter().GetY() - t.GetCenter().GetY();

		if (tl >= 0 && tw <= 0)
		{
			double tm = t.GetCenter().GetY() - GetBR().GetY();
			double jm = GetTL().GetX() - t.GetCenter().GetX();
			if (jm <= 0)
				return top;
			if (tm <= 0)
				return right;
			double ndeg = 90 - (atan(tm / jm)* 180.0 / PI);

			if (abs(ndeg) <= deg)
				return top;
			else
				return right;
		}
		else if (tl >= 0 && tw >= 0)
		{
			double tm = GetTL().GetY() - t.GetCenter().GetY();
			double jm = GetTL().GetX() - t.GetCenter().GetX();
			if (jm <= 0)
				return bottom;
			if (tm <= 0)
				return right;
			double ndeg = 90 - (atan(tm / jm)* 180.0 / PI);

			if (abs(ndeg) <= deg)
				return bottom;
			else
				return right;
		}
		else if (tl <= 0 && tw <= 0)
		{
			double tm = t.GetCenter().GetY() - GetBR().GetY();
			double jm = t.GetCenter().GetX() - GetBR().GetX();
			if (jm <= 0)
				return top;
			if (tm <= 0)
				return left;
			double ndeg = 90 - (atan(tm / jm)* 180.0 / PI);
			if (abs(ndeg) <= deg)
				return top;
			else
				return left;
		}
		else
		{
			double tm = GetTL().GetY() - t.GetCenter().GetY();
			double jm = t.GetCenter().GetX() - GetBR().GetX();
			if (jm <= 0)
				return bottom;
			if (tm <= 0)
				return left;
			double ndeg = 90 - (atan(tm / jm)* 180.0 / PI);

			if (abs(ndeg) <= deg)
				return bottom;
			else
				return left;
		}
	}

	else if(tl < tw)
	{
		deg = atan(tw / tl)* 180.0 / PI;
		tl = GetCenter().GetX() - t.GetCenter().GetX();
		tw = GetCenter().GetY() - t.GetCenter().GetY();
		if (tl >= 0 && tw <= 0)
		{
			double tm = t.GetCenter().GetY() - GetBR().GetY();
			double jm = GetTL().GetX() - t.GetCenter().GetX();
			if (jm <= 0)
				return top;
			if (tm <= 0)
				return right;
			double ndeg = (atan(tm / jm)* 180.0 / PI);

			if (abs(ndeg) <= deg)
				return right;
			else
				return top;
		}
		else if (tl >= 0 && tw >= 0)
		{
			double tm = GetTL().GetY() - t.GetCenter().GetY();
			double jm = GetTL().GetX() - t.GetCenter().GetX();
			if (jm <= 0)
				return bottom;
			if (tm <= 0)
				return right;
			double ndeg = (atan(tm / jm)* 180.0 / PI);

			if (abs(ndeg) <= deg)
				return right;
			else
				return bottom;
		}
		else if (tl <= 0 && tw <= 0)
		{
			double tm = t.GetCenter().GetY() - GetBR().GetY();
			double jm = t.GetCenter().GetX() - GetBR().GetX();
			if (jm <= 0)
				return top;
			if (tm <= 0)
				return left;
			double ndeg = (atan(tm / jm)* 180.0 / PI);
			if (abs(ndeg) <= deg)
				return left;
			else
				return top;
		}
		else
		{
			double tm = GetTL().GetY() - t.GetCenter().GetY();
			double jm = t.GetCenter().GetX() - GetBR().GetX();
			if (jm <= 0)
				return bottom;
			if (tm <= 0)
				return left;
			double ndeg = (atan(tm / jm)* 180.0 / PI);

			if (abs(ndeg) <= deg)
				return left;
			else
				return bottom;
		}
	}
}


double AABB::Overlap(AABB t,short direction)
{
	double overlap = 0;
	double a = GetWid() / 2;
	double b = t.GetWid() / 2;
	double c = t.GetCenter().GetY();
	double d = GetCenter().GetY();
	switch (direction)
	{
	case top:
		overlap = (GetWid() / 2) + (t.GetWid() / 2) - (t.GetCenter().GetY() - GetCenter().GetY());
		/*
		if (overlap > 0)
			return overlap;
		return 0;*/
		return overlap * (overlap > 0);
	case bottom:
		overlap = (GetWid() / 2) + (t.GetWid() / 2) - (GetCenter().GetY() - t.GetCenter().GetY());
		/*if (overlap > 0)
			return overlap;
		return 0;*/
		return overlap * (overlap > 0);
	case left:
		overlap = (GetLen() / 2) + (t.GetLen() / 2) - (t.GetCenter().GetX() - GetCenter().GetX());
		/*if (overlap > 0)
			return overlap;
		return 0;*/
		return overlap * (overlap > 0);
	case right:
		overlap = (GetLen() / 2) + (t.GetLen() / 2) - (GetCenter().GetX() - t.GetCenter().GetX());
		/*if (overlap > 0)
			return overlap;
		return 0;*/
		return overlap * (overlap > 0);
	}
}

bool AABB::intersection(AABB *range) {
	if (this == range)
		return true;
	else return false;
};
