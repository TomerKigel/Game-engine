#include "Player.h"
#include "StaticObject.h"
#include "Monster.h"
#include "Factory.h"

#define PI 3.14159265

Player::Player(AABB range, double hp, double ad, double spd, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt) : Living(hp, ad)
{
	space = range;
	sf::Vector2f cor(range.GetTL().GetX(), range.GetTL().GetY());
	if (txt == nullptr)
	{
		sf::Vector2f siz(range.GetWid(), range.GetLen());
		mdisp = std::make_shared<Graphics>(cor, siz, window);
	}
	else
	{
		mdisp = std::make_shared<Graphics>(cor, txt, window, &space);
		std::shared_ptr<Textures> t = Factory::CreatGameAssets();
		mdisp->AddResource(std::make_shared<sf::Texture>(*t->getTexture("yeti.png")), "yeti", nullptr);
	}
	PhysicsStats pps;
	pps.topspeed = 5;
	pps.accx = 0;
	pps.accy = 0;
	pps.topacc = 100;
	pps.xspeed = 0;
	pps.yspeed = 0;
	ph.setObjectsParameters(pps);
	SetHealth(100);
	refreshLastSpace();
	space.SetOwner(this);
	animantioncooldown.SetTimerMaxAsSeconds(0.05);
	attspd.SetTimerMaxAsSeconds(0.5);
	dashcooldown.SetTimerMaxAsSeconds(0.7);
	jumpcooldown.SetTimerMaxAsSeconds(0.5);
	invulnerable.SetTimerMaxAsSeconds(1);
	minv.SetTimerMaxAsSeconds(0.35);
	playerview.setSize(1980, 1080);
	playerview.setCenter(space.GetCenter().GetX(), space.GetCenter().GetY());
	zm = 1;
}


void Player::Move(double xspd, double yspd)
{
	space.SetTL(double(space.GetTL().GetX() + xspd), double(space.GetTL().GetY() + yspd));
	space.SetBR(double(space.GetBR().GetX() + xspd), double(space.GetBR().GetY() + yspd));
	PViewAdjustLoop(xspd, yspd);
}

void Player::amidead()
{
	if (!isLiving())
		Player::~Player();
}

void Player::draw()
{
	refreshLastSpace();
	sf::Vector2f p(space.GetTL().GetX(), space.GetTL().GetY());
	refreshgraphics(p);
	if (animantioncooldown.IsTimeUp()) {
		mdisp->switchToNextFrame();
		animantioncooldown.resetTimer();
	}
	HealthToSpd();
	double tnfc = (HealthPoints / maxHealthPoints) * 255;
	mdisp->changeColor(tnfc, tnfc, 0 , 0);
	mdisp->Draw();
}

short Player::reType()
{
	return ply;
}

void Player::refreshgraphics(sf::Vector2f pos)
{
	mdisp->refreshPosition(pos);
	if(invulnerable.IsTimeUp())
		mdisp->changeColor(0,0,0,255);
}

Player::~Player()
{
}

void Player::Controls()
{
	if (dashcooldown.IsTimeUp())
		ps.moving_state = non_moving;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (minv.IsTimeUp()) {
				inp.LeftArrowKey = true;
				if (ps.moving_state != dashing_right && ps.moving_state != dashing_left) {
					ps.moving_state = moving_left;
					if (mdisp->reDir() == right)
						mdisp->FlipHorizontali();
					Accelerate(-3, 0);
					ps.looking_state = lookingleft;
				}
			}
		}
	else
	{
		inp.LeftArrowKey = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (minv.IsTimeUp()) {
				inp.RightArrowKey = true;
				if (ps.moving_state != dashing_right && ps.moving_state != dashing_left) {
					ps.moving_state = moving_right;
					if (mdisp->reDir() == left)
						mdisp->FlipHorizontali();
					Accelerate(3, 0);
					ps.looking_state = lookingright;
				}
			}
		}
	else
	{
		inp.RightArrowKey = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (minv.IsTimeUp()) {
				inp.UpArrowKey = true;

				if (ps.jump == non_jump && reStamina() >= 10 && jumpcooldown.IsTimeUp()) {
					DecStamina(0);
					ps.jump = jumping;
					Accelerate(0, -11.5);
					std::shared_ptr<Sound> s = nullptr;
					s = Factory::CreateSound();
					jumpsound.setBuffer(s->reSfx()->at(1).sbuf);
					jumpsound.play();
				}
				else if (ps.jump == jumping && ph.reSpeed().GetY() >= 0 && reStamina() >= 5)
				{
					DecStamina(5);
					ps.jump = double_jumping;
					Accelerate(0, -9.5);
				}
				else if (ps.jump == side_hold)
				{
					ps.jump = jumping;
					if (ps.looking_state == lookingleft)
					{
						Accelerate(5, -11.5);
					}
					else if (ps.looking_state == lookingright)
					{
						Accelerate(-5, -11.5);
					}
				}
			}
		}
	else
	{
		inp.UpArrowKey = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (minv.IsTimeUp()) {
				inp.DownArrowKey = true;
				Accelerate(0, 10);
				ps.jump = bomb_dropping;
			}
		}
	else
	{
		inp.DownArrowKey = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
		{
			inp.FKey = true;
			Physics::GravityFlip();
		}
	else
	{
		inp.FKey = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{
		if (attspd.IsTimeUp()) {
			Point t = space.GetBR();
			if (mdisp->GetCurrResourceName() == "yeti")
			{
				space.SetBR(t.GetX() - 30, t.GetY() - 30);
				mdisp->ChangeResourceTo("original");
			}
			else if (mdisp->GetCurrResourceName() == "original") {
				space.SetBR(t.GetX() + 30, t.GetY() + 30);
				mdisp->ChangeResourceTo("yeti");
			}
			attspd.resetTimer();
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			inp.Akey = true;
			if (attspd.IsTimeUp()) {
				ps.attack = init_attack;
				std::shared_ptr<Sound> s = nullptr;
				s = Factory::CreateSound();
				attacksound.setBuffer(s->reSfx()->at(0).sbuf);
				attacksound.play();
				Factory::SetUpsk::SetUpSkill(&space, mdisp->rewin(), "swash.png", shared_from_this());
				Factory::CreateSkill();
				attspd.resetTimer();
			}
		}
	else
	{
		inp.Akey = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
				inp.LShiftKey = true;
				switch (ps.looking_state)
				{
				case lookingright:
					ps.moving_state = dashing_right;
					Accelerate(10, 0);
					//DecStamina(30);
					break;
				case lookingleft:
					ps.moving_state = dashing_left;
					Accelerate(-10, 0);
					//DecStamina(30);
					break;
				}
		}
	else
	{
		inp.LShiftKey = false;
	}
		/*if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			sf::Vector2i mpos = sf::Mouse::getPosition();
			double tx = mpos.x - space.GetCenter().GetX();
			double ty = mpos.y - space.GetCenter().GetY();
			double nt = std::atan(ty / tx) * 180 / PI;
			//double nt = tx / (sqrt(tx + ty) * sqrt(tx));
			//nt = std::acos(nt) * 180 / PI;
			if (mpos.x - space.GetCenter().GetX() > 0) {
				//Accelerate(0.15 * cos((nt)* PI / 180.0), 0.15 * sin((nt)* PI / 180.0));
				//Move(15 * cos((nt)* PI / 180.0), 15 * sin((nt)* PI / 180.0));
			}
			if (mpos.x - space.GetCenter().GetX() < 0 && mpos.y - space.GetCenter().GetY() < 0)
			{
				//Accelerate(0.15 * cos((nt - 180)* PI / 180.0), 0.15 * sin((nt - 180)* PI / 180.0));
				//Move(15 * cos((nt-180)* PI / 180.0), 15 * sin((nt-180)* PI / 180.0));
			}
			if (mpos.x - space.GetCenter().GetX() < 0 && mpos.y - space.GetCenter().GetY() > 0)
			{
				//Accelerate(0.15 * cos((nt + 180)* PI / 180.0), 0.15 * sin((nt + 180)* PI / 180.0));
				//Move(15 * cos((180 + nt)* PI / 180.0), 15 * sin((180 + nt)* PI / 180.0));
			}
		}*/
}

void Player::intersection(Object *obj)
{
	switch (obj->reType())
	{
	case mnstr:
	{
		Monster *p = dynamic_cast<Monster*>(obj);
		if (p->reMType() == bat) {
			if (invulnerable.IsTimeUp()) {
				GotHit();
				DecHealth(p->getAttack());
				switch(ps.looking_state)
				{
				case lookingleft:
					ph.intersection(true, false, left);
					Accelerate(10,0);
					break;
				case lookingright:
					ph.intersection(true, false, right);
					Accelerate(-10,0);
					break;
				}
			}
		}
		break;
	}
	case itm:
	{
		IncHealth(10);
		std::shared_ptr<Sound> s = nullptr;
		s = Factory::CreateSound();
		attacksound.setBuffer(s->reSfx()->at(1).sbuf);
		attacksound.play();
		break;
	}
	case skill:
	{
		Skill *p = dynamic_cast<Skill*>(obj);
		if (p->returnowner()->reType() == mnstr && invulnerable.IsTimeUp())
		{
			double att = std::dynamic_pointer_cast<Monster>(p->returnowner())->getAttack();
			DecHealth(att);
			GotHit();
		}
		break;
	}
	case sttc:
	{
		
		AABB *t = this->getSpace();
		short dir = 0;
		double overlap = 0;
		StaticObject *sptr = dynamic_cast<StaticObject*>(obj);
		dir = Lastspace.WIRTTO(*sptr->getSpace());
		overlap = getSpace()->Overlap(*sptr->getSpace(), dir);
		PhysicsIntersection(dir, overlap);
		if (dir == top) {
			ps.collision_state = OnGround;
			ps.jump = non_jump;
		}
		if (dir == left || dir == right) {
			ps.jump = side_hold;
			ps.collision_state = In_air;
		}
		break;
	}
	}
}

void Player::PViewAdjustLoop(double xspd, double yspd)
{
	if(space.GetCenter().GetX() > mdisp->rewin()->getView().getCenter().x + 300)
		playerview.move(xspd, 0);
	else if (space.GetCenter().GetX() < mdisp->rewin()->getView().getCenter().x - 300)
		playerview.move(xspd, 0);
	if(space.GetCenter().GetY() > mdisp->rewin()->getView().getCenter().y + 200)
		playerview.move( 0, yspd);
	else if (space.GetCenter().GetY() < mdisp->rewin()->getView().getCenter().y - 200)
		playerview.move(0, yspd);
	mdisp->rewin()->setView(playerview);
}

void Player::HealthToSpd()
{
	ph.setTopSpeed(5 * (HealthPoints / maxHealthPoints));
}

void Player::GotHit()
{
	if (!isLiving())
		destroy();
	mdisp->changeColor(0, 0, 0, 155);
	invulnerable.resetTimer();
	minv.resetTimer();
}

states Player::reState()
{
	return ps;
}

void Player::PushBack(short direction)
{
	if (direction == lookingleft)
		Move(-30, 0);
	if (direction == lookingright)
		Move(30, 0);
}