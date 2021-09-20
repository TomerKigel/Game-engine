#include "Yeti.h"
#include "Factory.h"

Yeti::Yeti(double tspd,AABB range, double hp, double ad, double spd, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt) : Monster(range,hp,ad,spd,window,txt)
{
	attTimer.SetTimerMaxAsSeconds(1.5);
	ph.setTopSpeed(tspd);
}

void Yeti::Controls()
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
			else if (disfedge.GetX() < 120)
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
			if (focus->GetCenter().GetX() < GetCenter().GetX())
			{
				if (g < 17) {
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
				}
				if (g > 16) {
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
			}
			else
			{
				if (g < 17) {
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
				if (g > 16) {
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
				}
			}
			if (focus->GetCenter().GetY() < GetCenter().GetY() && jcd.IsTimeUp())
			{
				jcd.resetTimer();
				Accelerate(0, -10);
			}
			if (focus->GetCenter().GetX() - GetCenter().GetX() < 30 && focus->GetCenter().GetX() - GetCenter().GetX() > -30)
			{
				Attack();
			}
		}
		cd.resetTimer();
	}
}

bool Yeti::intersection(AABB *ab)
{
	Object* obj = static_cast<Object*>(ab);
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
			setFocus(tpl->getAABB());
			DecHealth(30);
			//mdisp->changeColor(true);
			invulnerable.resetTimer();
			if (!isLiving()) {
				destroy();
				//short g = rand() % 6;
				if (tpl->ps.moving_state == dashing_left || tpl->ps.moving_state == dashing_right) {
					AABB s(GetBR().GetX() - 50, GetBR().GetY() - 50, GetBR().GetX(), GetBR().GetY());
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
		dir = Lastspace.WIRTTO(*sptr->getAABB());
		overlap = getAABB()->Overlap(*sptr->getAABB(), dir);
		PhysicsIntersection(dir, overlap);
		calcDisFromEdge(sptr);
		break;
	}
	return true;
}

short Yeti::reMType()
{
	return yeti;
}

void Yeti::Attack()
{
	if (attTimer.IsTimeUp()) {
		Factory::SetUpsk::SetUpSkill(getAABB(), mdisp->rewin(), "swash.png",shared_from_this());
		Factory::CreateSkill();
		attTimer.resetTimer();
	}
}
