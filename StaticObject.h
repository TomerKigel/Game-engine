#pragma once
#include "Object.h"
#include "Graphics.h"

class StaticObject : public Object , public std::enable_shared_from_this<StaticObject>
{
private:
	std::shared_ptr<Graphics> disp;
	sf::Texture tx;
	StaticObject();
protected:
public:
	////////////////////////////////////////////////////////////////////////////////////////
	//Constructor
	//
	//\param range     AABB of the object
	//\param window    window handle
	//\param txt       texture for displaying the object
	////////////////////////////////////////////////////////////////////////////////////////
	StaticObject(AABB range, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt);

	////////////////////////////////////////////////////////////////////////////////////////
	//Accessor function 
	//
	//\brief returns the type of the object 
	////////////////////////////////////////////////////////////////////////////////////////
	virtual short reType() { return sttc; }

	////////////////////////////////////////////////////////////////////////////////////////
	//Display function 
	//
	//\brief Displays object on screen via window handle 
	////////////////////////////////////////////////////////////////////////////////////////
	void draw();

	////////////////////////////////////////////////////////////////////////////////////////
	//collision resolution		
	//
	//\brief   resolves intersection with different object types								
	////////////////////////////////////////////////////////////////////////////////////////
	bool intersection(AABB *obj);

	////////////////////////////////////////////////////////////////////////////////////////
	//Default Destructor															
	////////////////////////////////////////////////////////////////////////////////////////
	~StaticObject(){}
};