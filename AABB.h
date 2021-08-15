#pragma once

#include "Point.h"
#include "Object.h"
#include <memory>

class Object;

class AABB : public std::enable_shared_from_this<AABB>
{
private:
	// T = top 
	// B = bottom
	// L = left 
	// R = right 
	Point TL;
	Point BR;

public:
	Object *ownerptr;

	//Default constructor
	AABB() {}

	////////////////////////////////////////////////////////////////////////////////////////
	//Default constructor																	
	//\brief   sets the values for the top left and bottom right points describing the AABB using x and y coordinates	
	//\param tlx   Top Left X cooridante														
	//\param tly   Top Left Y cooridante														
	//\param brx   Bottom Right X cooridante												    
	//\param brx   Bottom Right Y cooridante													
	////////////////////////////////////////////////////////////////////////////////////////
	AABB(double tlx, double tly, double brx, double bry, Object *owner = nullptr);
	

	////////////////////////////////////////////////////////////////////////////////////////
	//Default constructor Point use		
	//
	//\comment  see Point class documentation before the use of this function
	//
	//\brief   sets the values for the top left and bottom right points describing the AABB	using Points
	//\param tl   Top Left Point													
	//\param br   Bottom Right Point																										
	////////////////////////////////////////////////////////////////////////////////////////
	AABB(Point tl, Point br, Object *owner = nullptr);

	//accessor - return the value center of the AABB
	Point GetCenter();

	//accessor - return the value of the length
	int GetLen();
	
	//accessor - return the value of the width
	int GetWid();

	//accessor - return the Point TL
	Point GetTL();

	//accessor - return the Point BR
	Point GetBR();

	//accessor - returns this pointer
	AABB *getAABB();

	////////////////////////////////////////////////////////////////////////////////////////
	//Test Function													
	//\brief  tests if the range of this AABB intersects with the range of the given parameter			
	//\param range   AABB for comparison												
	///////////////////////////////////////////////////////////////////////////////////////
	bool operator==(AABB &range);

	////////////////////////////////////////////////////////////////////////////////////////
	//Test Function													
	//\brief  tests if the range of this AABB is 1 pixel away from the range sent to the function			
	//\param range   AABB for comparison												
	///////////////////////////////////////////////////////////////////////////////////////
	int AABB::operator-=(AABB &range);

	////////////////////////////////////////////////////////////////////////////////////////
	//Test Function													
	//\brief  tests if the range of this AABB intersects with the range of the given parameter			
	//\param range   AABB for comparison												
	///////////////////////////////////////////////////////////////////////////////////////
	void operator*=(double f);

	////////////////////////////////////////////////////////////////////////////////////////
	//Test Function													
	//\brief  tests if the range of this AABB contains a given point				
	//\param pnt   point to find in the AABB's range												
	///////////////////////////////////////////////////////////////////////////////////////
	bool isContaining(Point pnt);

	////////////////////////////////////////////////////////////////////////////////////////
	//Copy Function														
	//\brief  Sets AABB's values to the values of param origin				
	//\param origin   AABB to copy from												
	///////////////////////////////////////////////////////////////////////////////////////
	void operator=(AABB &origin);


	////////////////////////////////////////////////////////////////////////////////////////
	//Mutator Function														
	//\brief  Sets TL values				
	//\param x   x coordinate of TL		
	//\param y   y coordinate of TL	
	///////////////////////////////////////////////////////////////////////////////////////
	void SetTL(double x, double y);
	////////////////////////////////////////////////////////////////////////////////////////
	//Mutator Function														
	//\brief  Sets BR values				
	//\param x   x coordinate of BR	
	//\param y   y coordinate of BR												
	///////////////////////////////////////////////////////////////////////////////////////
	void SetBR(double x, double y);


	////////////////////////////////////////////////////////////////////////////////////////
	//ownership changer													
	//\brief  Changes ownership of the AABB					
	//\param ptr   new owner reference   											
	///////////////////////////////////////////////////////////////////////////////////////
	void SetOwner(Object *ptr);


	////////////////////////////////////////////////////////////////////////////////////////
	//Intersection helper function												
	//\brief  returns where an object is in relation to another. (top,bottom,left or right)			
	//\param t   AABB of the object to be tested 											
	///////////////////////////////////////////////////////////////////////////////////////
	short WIRTTO(AABB t);

	////////////////////////////////////////////////////////////////////////////////////////
	//Intersection helper function												
	//\brief  returns a value for either x or y axis amount of overlap,depending on direction 			
	//\param t			 AABB of the object to be tested 	
	//\param direction   where is t parameter in relation current object(derived from WIRTTO)	
	///////////////////////////////////////////////////////////////////////////////////////
	double Overlap(AABB t, short direction);

	//Default Destructor
	~AABB() {}
};
