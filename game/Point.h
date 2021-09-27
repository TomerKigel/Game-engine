#pragma once

class Point
{
private:
	double X, Y;

public:
	//Default constructor
	Point() {}

	//Argument constructor
	Point(double Xcor, double Ycor);

	//Copy constructor
	Point(Point &p);

	//Copy function, copies the value of x and y 
	void operator=(Point &p);

	//////////////////////////////////////////////////////////////////////
	//TEST FUNCTION														//
	//\brief compares points											//
	//\param pnt	Point refrence										//
	//////////////////////////////////////////////////////////////////////
	bool operator==(Point &pnt);

	//Accessor - return the value of X
	double GetX();
	//Accessor - return the value of Y
	double GetY();

	//Mutator - Set the value of X
	void SetX(double nx);
	//Mutator - Set the value of Y
	void SetY(double ny); 

	//Default Destructor
	~Point() {}
};
