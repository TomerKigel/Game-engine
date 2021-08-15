#include "Monster.h"
#include "StaticObject.h"
#include "Player.h"
#include "Factory.h"
#include "Skill.h"

Monster::Monster(AABB range, double hp, double ad,double spd, std::shared_ptr<sf::RenderWindow> window , std::shared_ptr<sf::Texture> txt) : Living(hp, ad)
{
	space = range;
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr) 
	{
		sf::Vector2f siz(range.GetLen(),range.GetWid());
		mdisp = std::make_shared<Graphics>(cor, siz, window);
	}
	else
	{
		mdisp = std::make_shared<Graphics>(cor, txt, window , &space);
	}
	PhysicsStats pps;
	pps.topspeed = 5;
	pps.accx = 0;
	pps.accy = 0;
	pps.topacc = 100;
	pps.xspeed = 0;
	pps.yspeed = 0;
	ph.setObjectsParameters(pps);
	refreshLastSpace();
	focus = nullptr;
	cd.SetTimerMaxAsSeconds(0.1);
	jcd.SetTimerMaxAsSeconds(1.5);
	invulnerable.SetTimerMaxAsSeconds(0.5);
	animantioncooldown.SetTimerMaxAsSeconds(0.1);
	mnstrstate.looking_state = lookingright;
	space.SetOwner(this);
}


void Monster::Move(double xspd, double yspd)
{
	space.SetTL(space.GetTL().GetX() + xspd, space.GetTL().GetY() + yspd);
	space.SetBR(space.GetBR().GetX() + xspd, space.GetBR().GetY() + yspd);
}

void Monster::draw()
{
	refreshLastSpace();
	if (animantioncooldown.IsTimeUp()) {
		mdisp->switchToNextFrame();
		animantioncooldown.resetTimer();
	}
	sf::Vector2f p(space.GetTL().GetX(), space.GetTL().GetY());
	refreshgraphics(p);
	double tnfc = (HealthPoints / maxHealthPoints) * 255;
	mdisp->changeColor(tnfc, tnfc, 0 , 0);
	mdisp->Draw();
}

short Monster::reType()
{
	return mnstr;
}

void Monster::refreshgraphics(sf::Vector2f pos)
{
	mdisp->refreshPosition(pos);
}

Monster::~Monster()
{
}

void Monster::setFocus(AABB *cofob)
{
	focus = cofob;
}

void Monster::Controls()
{
	if (cd.IsTimeUp()) {
		int g = 0;
		if (focus == nullptr) {
			if (disfedge.GetX() > 120 && disfedge.GetY() > 120) {
				g = rand() % 19;
				if (g > 11 && jcd.IsTimeUp())
				{
					jcd.resetTimer();
					Accelerate(0, -10);
				}
				if (g > 5 && g < 12) {
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
				}
				if (g < 6) {
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
			}
			else if(disfedge.GetX() < 120)
			{
				g = rand() % 12;
				if (g % 2 == 0 && g < 6)
					Accelerate(3, 0);
			}
			else
			{
				g = rand() % 12;
				if (g % 2 != 0 && g < 6)
				Accelerate(-3, 0);
			}
		}
		else
		{
			g = rand() % 19;
			if (focus->GetCenter().GetX() < space.GetCenter().GetX())
			{
				if (g < 17) {
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
				}
				else{
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
			}
			else
			{
				if (g < 20) {
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
				else{
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
					}
			}
			if (focus->GetCenter().GetY() < space.GetCenter().GetY() && jcd.IsTimeUp())
			{
				jcd.resetTimer();
				Accelerate(0, -10);
			}
		}
		cd.resetTimer();
	}
}

void Monster::calcDisFromEdge(StaticObject *obj)
{
	double ti = space.GetCenter().GetX() - obj->getSpace()->GetTL().GetX();
	double pi = obj->getSpace()->GetBR().GetX() - space.GetCenter().GetX();
	disfedge.SetX(ti);
	disfedge.SetY(pi);
}

void Monster::PushBack(short direction)
{
	if (direction == lookingleft)
		Move(-30, 0);
	if (direction == lookingright)
		Move(30, 0);
}

short Monster::reMType()
{
	return basemonster;
}

void Monster::cc()
{
	mdisp->changeColor(true);
}

void Monster::intersection(Object *obj)
{
	switch (obj->reType())
	{
	case skill:
	{
		Skill *p = dynamic_cast<Skill*>(obj);
		if (p->returnowner()->reType() == ply && invulnerable.IsTimeUp())
		{
			std::shared_ptr<Player> tpl = std::dynamic_pointer_cast<Player>(p->returnowner());
			PushBack(tpl->reState().looking_state);
			tpl->IncStamina(20);
			setFocus(tpl->getSpace());
			DecHealth(30);
			//mdisp->changeColor(true);
			invulnerable.resetTimer();
			if (!isLiving()) {
				destroy();
				//short g = rand() % 6;
				if (tpl->ps.moving_state == dashing_left || tpl->ps.moving_state == dashing_right) {
					AABB s(space.GetBR().GetX() - 50, space.GetBR().GetY() - 50, space.GetBR().GetX(), space.GetBR().GetY());
					Factory::SetUpItm::SetUpItem(&s, mdisp->rewin(), "HealthPotion.png");
					Factory::CreateItem();
				}
			}
		}
		break;
	}
	case ply:
		//setFocus(dynamic_cast<Player*>(obj)->getSpace());
		//MakeAggresive();
		break;
	case sttc:
		short dir = 0;
		double overlap = 0;
		StaticObject *sptr = dynamic_cast<StaticObject*>(obj);
		dir = Lastspace.WIRTTO(*sptr->getSpace());
		overlap = getSpace()->Overlap(*sptr->getSpace(), dir);
		PhysicsIntersection(dir, overlap);
		calcDisFromEdge(sptr);
		break;
	}
}
