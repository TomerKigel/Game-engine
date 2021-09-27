#include "Bat.h"
#include "Factory.h"

Bat::Bat(double opthight, double tspd, AABB range, double hp, double ad, double spd, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt) : Monster(range, hp, ad, spd, window, txt)
{
	ohight = opthight;
	attTimer.SetTimerMaxAsSeconds(0.5);
	ph.setTopSpeed(tspd);
	ph.UnEffectedByGravity();
	cd.SetTimerMaxAsSeconds(0.2);
}

void Bat::Controls()
{
	if (cd.IsTimeUp()) {
		if (focus == nullptr) {
			int g = 0, f = 0,at;
			at = rand() % 500;
			if (at == 4)
			{
				Accelerate(0, 10);
			}
			f = rand() % 2;
			if (ohight - GetCenter().GetY() <= 50 && ohight - GetCenter().GetY() >= -50)
				g = rand() % 2;
			else if (ohight - GetCenter().GetY() > 50)
				g = 0;
			else if (ohight - GetCenter().GetY() < -50)
				g = 1;
			if (f == 0)
			{
				if (mnstrstate.looking_state == lookingleft) {
					mdisp->FlipHorizontali();
					mnstrstate.looking_state = lookingright;
				}
				Accelerate(2, 0);
			}
			if (f == 1)
			{
				if (mnstrstate.looking_state == lookingright) {
					mdisp->FlipHorizontali();
					mnstrstate.looking_state = lookingleft;
				}
				Accelerate(-2, 0);
			}
			if (g == 0)
			{
				Accelerate(0, 1);
			}
			if (g == 1)
			{
				Accelerate(0, -1);
			}
		}
		else
		{
			if (attTimer.IsTimeUp())
			{
				attTimer.resetTimer();
				if (focus->GetCenter().GetX() - GetCenter().GetX() < 100 && focus->GetCenter().GetX() - GetCenter().GetX() > -100)
				{
					if (focus->GetCenter().GetY() > GetCenter().GetY())
						Accelerate(0, 10);
				}
				
			}
				int g = 0, f = 0;
				f = rand() % 20;
				if (ohight - GetCenter().GetY() <= 50 && ohight - GetCenter().GetY() >= -50)
					g = rand() % 2;
				else if (ohight - GetCenter().GetY() > 50)
					g = 0;
				else if (ohight - GetCenter().GetY() < -50)
					g = 1;
				if (focus->GetCenter().GetX() < GetCenter().GetX())
				{
					if (f < 15) {
						if (mnstrstate.looking_state == lookingright) {
							mdisp->FlipHorizontali();
							mnstrstate.looking_state = lookingleft;
						}
						Accelerate(-2, 0);
					}
					else {
						if (mnstrstate.looking_state == lookingleft) {
							mdisp->FlipHorizontali();
							mnstrstate.looking_state = lookingright;
						}
						Accelerate(3, 0);
					}
				}
				else
				{
					if (f < 15) {
						if (mnstrstate.looking_state == lookingleft) {
							mdisp->FlipHorizontali();
							mnstrstate.looking_state = lookingright;
						}
						Accelerate(3, 0);
					}
					else {
						if (mnstrstate.looking_state == lookingright) {
							mdisp->FlipHorizontali();
							mnstrstate.looking_state = lookingleft;
						}
						Accelerate(-2, 0);
					}
				}
				if (g == 0)
				{
					Accelerate(0, 1);
				}
				if (g == 1)
				{
					Accelerate(0, -1);
				}
		}
		cd.resetTimer();
	}
}

bool Bat::intersection(AABB *ab)
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
		//setFocus(dynamic_cast<Player*>(obj)->getAABB());
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

short Bat::reMType()
{
	return bat;
}

short Bat::reType()
{
	return mnstr;
}
