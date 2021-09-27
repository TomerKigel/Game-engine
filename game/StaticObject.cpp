#include "StaticObject.h"

StaticObject::StaticObject(AABB range, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt)
{
	setAABB(range);
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr)
	{
		sf::Vector2f siz(range.GetLen(), range.GetWid());
		disp = std::make_shared<Graphics>(cor, siz, window);
	}
	else
	{
		disp = std::make_shared <Graphics>(cor, txt, window, getAABB());
	}
}

void StaticObject::draw()
{
	disp->Draw();
}


bool StaticObject::intersection(AABB *ab)
{
	Object* obj = static_cast<Object*>(ab);
	switch (obj->reType())
	{
	case ply:
		break;
	case mnstr:
		break;
	}
	return true;
}
