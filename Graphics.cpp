#include "Graphics.h"
#include "Factory.h"

Graphics::Graphics(sf::Vector2f tlc, sf::Vector2f size, std::shared_ptr<sf::RenderWindow> win, AABB *sizeofobj)
{
	window = win;
	wtod = BOX;
	gbox.setPosition(tlc);
	gbox.setSize(size);
	gbox.setFillColor(sf::Color::Blue);
	direction = right;
	CurrentTB = 0;
}
Graphics::Graphics(sf::Vector2f tlc, std::shared_ptr<sf::Texture> texture, std::shared_ptr<sf::RenderWindow> win, AABB *sizeofobj)
{
	CurrentTB = 0;
	window = win;
	wtod = SPR;
	TexBuf tb{ texture, "original" ,1,1,1,1,1,nullptr};
	sf::Vector2u a = tb.localtx->getSize();
	spr.setTexture(*tb.localtx);
	direction = right;

	if (sizeofobj != nullptr) {
		if (a.x < sizeofobj->GetLen()) {
			sf::IntRect j(0, 0, sizeofobj->GetLen(), sizeofobj->GetWid());
			tb.localtx->setRepeated(true);
			spr.setTextureRect(j);
		}
		tb.taf = sizeofobj;
		if (a.x > sizeofobj->GetLen()) {
			if (a.x % sizeofobj->GetLen() != 0)
			{
				tb.colmns = 1+(a.x / sizeofobj->GetLen());
			}
			else
			{
				tb.colmns = a.x / sizeofobj->GetLen();
			}
			if (a.y % sizeofobj->GetWid() != 0)
			{
				tb.rows = 1 + (a.y / sizeofobj->GetWid());
			}
			else 
			{
				tb.rows = a.y / sizeofobj->GetWid();
			}
			sf::IntRect r1(0, 0, sizeofobj->GetLen(), sizeofobj->GetWid());
			spr.setTextureRect(r1);
			tb.framesintxt = tb.rows * tb.colmns;
		}
		else if (sizeofobj->GetLen() == a.x)
			tb.taf = nullptr;
	}
	TB.push_back(tb);
	spr.setPosition(tlc);
}
Graphics::Graphics(sf::Vector2f tlc, std::string filename, std::shared_ptr<sf::RenderWindow> win, AABB *sizeofobj)
{
	CurrentTB = 0;
	std::shared_ptr<Textures> t = Factory::CreatGameAssets();
	TexBuf tb{ std::make_shared<sf::Texture>(*t->getTexture(filename)) ,"original" ,1,1,1,1,1,nullptr };
	//sf::Texture *texture = t->getTexture(filename);
	window = win;
	wtod = SPR;
	sf::Vector2u a = tb.localtx->getSize();
	spr.setTexture(*tb.localtx);
	//framesintxt = 1;
	//rows = 1;
	//currframe = 1;
	//currrow = 1;
	direction = right;

	if (sizeofobj != nullptr) {
		tb.taf = sizeofobj;
		if (a.x > sizeofobj->GetLen()) {
			if (a.x % sizeofobj->GetLen() != 0)
			{
				tb.colmns = 1 + (a.x / sizeofobj->GetLen());
			}
			else
			{
				tb.colmns = a.x / sizeofobj->GetLen();
			}
			if (a.y % sizeofobj->GetWid() != 0)
			{
				tb.rows = 1 + (a.y / sizeofobj->GetWid());
			}
			else
			{
				tb.rows = a.y / sizeofobj->GetWid();
			}
			sf::IntRect r1(0, 0, sizeofobj->GetLen(), sizeofobj->GetWid());
			spr.setTextureRect(r1);
			tb.framesintxt = tb.rows * tb.colmns;
		}
		else if (sizeofobj->GetLen() == a.x)
			tb.taf = nullptr;
	}
	TB.push_back(tb);
	spr.setPosition(tlc);
}
void Graphics::Draw()
{
	switch (wtod)
	{
	case BOX:
		window->draw(gbox);
		gbox.setFillColor(sf::Color::Blue);
		break;
	case SPR:
		window->draw(spr);
		break;
	default:
		break;
	}
}

void Graphics::AddResource(std::shared_ptr<sf::Texture> texture, std::string name, AABB *sizeofobj)
{
	TexBuf ntb{ texture,name,1,1,1,1,1,nullptr };
	sf::Vector2u a = ntb.localtx->getSize();
	if (sizeofobj != nullptr) {
		ntb.taf = sizeofobj;
		if (a.x > sizeofobj->GetLen()) {
			if (a.x % sizeofobj->GetLen() != 0)
			{
				ntb.colmns = 1 + (a.x / sizeofobj->GetLen());
			}
			else
			{
				ntb.colmns = a.x / sizeofobj->GetLen();
			}
			if (a.y % sizeofobj->GetWid() != 0)
			{
				ntb.rows = 1 + (a.y / sizeofobj->GetWid());
			}
			else
			{
				ntb.rows = a.y / sizeofobj->GetWid();
			}
			sf::IntRect r1(0, 0, sizeofobj->GetLen(), sizeofobj->GetWid());
			spr.setTextureRect(r1);
			ntb.framesintxt = ntb.rows * ntb.colmns;
		}
		else if (sizeofobj->GetLen() == a.x)
			ntb.taf = nullptr;
	}
	TB.push_back(ntb);
}

void Graphics::ChangeResourceTo(std::string name)
{
	for (int i = 0; i < TB.size(); i++)
	{
		if (TB[i].name == name) {
			spr.setTexture(*TB[i].localtx);
			CurrentTB = i;
		}
	}
}

std::string Graphics::GetCurrResourceName()
{
	return TB[CurrentTB].name;
}

std::shared_ptr<sf::RenderWindow> Graphics::rewin()
{
	return window;
}

void Graphics::refreshPosition(sf::Vector2f pos)
{
	gbox.setPosition(pos);
	spr.setPosition(pos);
}

Graphics::~Graphics()
{
}

void Graphics::changeColor(bool c)
{
	if (c) {
		gbox.setFillColor(sf::Color::Green);
		sf::Color sco = spr.getColor();
		sco.g = 0;
		sco.b = 0;
		sco.r = 255;
		spr.setColor(sco);
	}
	else
	{
		gbox.setFillColor(sf::Color::Blue);
		sf::Color sco = spr.getColor();
		sco.g = 255;
		sco.b = 255;
		sco.r = 255;
		spr.setColor(sco);
	}

}

void Graphics::changeColor(short g,short b,short r,short alpha) {
	sf::Color sco = spr.getColor();
	if(g != 0)
		sco.g = g;
	if(b != 0)
		sco.b = b;
	if(r != 0)
		sco.r = r;
	if (alpha != 0)
		sco.a = alpha;
	spr.setColor(sco);
}

void Graphics::switchToNextFrame()
{
	sf::IntRect r1;
	if (TB[CurrentTB].taf == nullptr)
	{
		sf::Texture t = *spr.getTexture();
		r1.width = spr.getTexture()->getSize().x;
		r1.left = (TB[CurrentTB].currframe - 1) * r1.width;
		if (direction == left) {
			r1.width = -r1.width;
			r1.left = TB[CurrentTB].currframe * (-r1.width);
		}
		r1.height = spr.getTexture()->getSize().y;
		r1.top = 0;
	}
	else if (direction == right)
	{
		r1.width = TB[CurrentTB].taf->GetLen();
		r1.height = TB[CurrentTB].taf->GetWid();
		r1.top = (TB[CurrentTB].currrow-1)* TB[CurrentTB].taf->GetWid();
		r1.left = (TB[CurrentTB].currframe-1) * TB[CurrentTB].taf->GetLen();
	}
	else if (direction == left)
	{
		r1.width = -TB[CurrentTB].taf->GetLen();
		r1.height = TB[CurrentTB].taf->GetWid();
		r1.top = (TB[CurrentTB].currrow-1)* TB[CurrentTB].taf->GetWid();
		r1.left = TB[CurrentTB].currframe * TB[CurrentTB].taf->GetLen();
	}

	spr.setTextureRect(r1);
	if (TB[CurrentTB].currframe < TB[CurrentTB].colmns)
		TB[CurrentTB].currframe++;
	else if(TB[CurrentTB].currrow < TB[CurrentTB].rows){
		TB[CurrentTB].currframe = 1;
		TB[CurrentTB].currrow++;
	}
	else
	{
		TB[CurrentTB].currframe = 1;
		TB[CurrentTB].currrow = 1;
	}
}

void Graphics::FlipHorizontali()
{
	if (direction == right)
	{
		direction = left;
	}
	else
	{
		direction = right;
	}
}

short Graphics::reDir()
{
	return direction;
}

void Graphics::setView(sf::View viewtoset)
{
	sf::Vector2f t = viewtoset.getCenter();
	t.x -= 990;
	t.y -= 540;
	spr.setPosition(t);
}
