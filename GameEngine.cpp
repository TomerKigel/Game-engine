#include "GameEngine.h"
#include "APH.h"

#define testnum 2

GameEngine::GameEngine(char *filename)
{
	window = std::make_shared<sf::RenderWindow>();
	window->create(sf::VideoMode(1920, 1080), "DashNBlood" ,3/*sf::Style::Resize*/);
	std::shared_ptr<sf::Texture> loadingtxt = std::make_shared<sf::Texture>();
	if (!loadingtxt->loadFromFile("loading.png"))
		throw("loading");
	Graphics loading(sf::Vector2f(0,0), loadingtxt,window);
	loading.Draw();
	window->display();
	std::shared_ptr<Textures> GameAssets = Factory::CreatGameAssets();
	//GameAssets->SetTexturesBuffer("bnn.png");
	//GameAssets->SetTexturesBuffer("HealthPotion.png");
	//GameAssets->SetTexturesBuffer("yeti.png");
	//GameAssets->SetTexturesBuffer("Background.png");
	//GameAssets->SetTexturesBuffer("swash.png");
	//GameAssets->SetTexturesBuffer("bat.png");
	s = Factory::CreateSound();
	Musicfilestream("MusicList.txt");
	Graphicsfilestream("GraphicsList.txt");
	theme.setBuffer(s->reSound()->at(0).sbuf);
	theme.setLoop(true);
	theme.play();
	me = std::make_shared<sf::Texture>();
	if (!me->loadFromFile("ast.png"))
		throw("ast error");
	gome = std::make_shared<sf::Texture>();
	if (!gome->loadFromFile("GameOver.png"))
		throw("GameOver error");
	menu = std::make_shared<Graphics>(sf::Vector2f(0, 0), me, window);
	gomenu = std::make_shared<Graphics>(sf::Vector2f(0, 0), gome, window);
	plyr = nullptr;
	isPaused = false;
}

void GameEngine::GameLoop()
{
	std::vector<AABB*> *mst;
	//Factory::SetUpStatic::SetUpStaticObject(0, 1020, 3000, 1300, window/*, "C:\\Users\\Tomer\\Documents\\Visual Studio 2015\\Projects\\LastAttempt\\df.png"*/);
	//Factory::CreatestaticObject();
	//Factory::SetUpStatic::SetUpStaticObject(200, 200, 800, 400, window/*, "C:\\Users\\Tomer\\Documents\\Visual Studio 2015\\Projects\\LastAttempt\\df.png"*/);
	//Factory::CreatestaticObject();
	//Factory::SetUpStatic::SetUpStaticObject(200, 200, 400, 800, window/*, "C:\\Users\\Tomer\\Documents\\Visual Studio 2015\\Projects\\LastAttempt\\df.png"*/);
	//Factory::CreatestaticObject();
	//Factory::SetUpItm::SetUpItem(210, 149, 260, 200, window, "HealthPotion.png");
	//Factory::CreateItem();

	mst = Factory::callobjectList();

	window->setFramerateLimit(60);

	/*for (short i = 0; i < 2 * testnum; i += 2)
		for (short p = 0; p < 2 * testnum; p += 2)
		{
			Factory::SetUpMstr::SetUpMonster(600 + p * 80, i * 80, 600 + p * 80 + 80, i * 80 + 80, 100, 5, 5, window);
			Factory::SetUpMstr::SetUpYeti(2, "yeti.png");
			Factory::CreateMonster("Yeti");
		}
	for (short i = 0; i < 2 * 2 * testnum; i += 2)
		for (short p = 0; p < 2 * 2 *testnum; p += 2)
		{
			int rhight = (rand() % 200) + 400;
			Factory::SetUpMstr::SetUpMonster(800 + p * 32, i * 32, 800 + p * 32 + 32, i * 32 + 32, 35, 15, 5, window);
			Factory::SetUpMstr::SetUpBat(rhight,2, "bat.png");
			Factory::CreateMonster("Bat");
		}

	Factory::SetUpPlyr::SetUpPlayer(1770, 0, 1820, 50, 100, 10, 10, window, "bnn.png");
	plyr = Factory::CreatePlayer();*/

	LoadFromFile("Map.txt");

	QuadTree QT(mst->at(0)->GetTL().GetX() - 1000, -10800, mst->at(mst->size() - 1)->GetTL().GetX() + 1000, 10800);
	sf::Clock clki;

	Physics::GravityOn();

	sf::Vector2f a(0, 0);
	Graphics ls(a, "Background.png", window,nullptr);

	while (window->isOpen())
	{
		window->clear();
		if (isPaused == false && GameOver == false) {
			window->clear();
			for (short i = 0; i < mst->size(); i++)
			{
				bool ti = mst->at(i)->ownerptr->isUpForDestruction();
				if (ti) {
					if (mst->at(i)->ownerptr->reType() == ply)
						GameOver = true;
					Factory::destoryObject(i);
				}
				/*
				switch (mst->at(i)->ownerptr->reType())
				{
				case ply:
					dynamic_cast<Player*>(mst->at(i)->ownerptr)->~Player();
					break;
				case mnstr:
					if(dynamic_cast<Monster*>(mst->at(i)->ownerptr)->reMType() == basemonster)
						dynamic_cast<Monster*>(mst->at(i)->ownerptr)->~Monster();
					else if(dynamic_cast<Monster*>(mst->at(i)->ownerptr)->reMType() == yeti)
						dynamic_cast<Yeti*>(mst->at(i)->ownerptr)->~Yeti();
					else if (dynamic_cast<Bat*>(mst->at(i)->ownerptr)->reMType() == bat)
						dynamic_cast<Bat*>(mst->at(i)->ownerptr)->~Bat();
					break;
				case itm:
					dynamic_cast<Item*>(mst->at(i)->ownerptr)->~Item();
					break;
				case sttc:
					dynamic_cast<StaticObject*>(mst->at(i)->ownerptr)->~StaticObject();
					break;
				case skill:
					dynamic_cast<Skill*>(mst->at(i)->ownerptr)->~Skill();
					break;
				}
				mst->erase(mst->begin() + i);
				mst->shrink_to_fit();
			}*/
			}

			/*sf::Clock clkkk;
			clkkk.restart().asSeconds();
			for (std::vector<AABB*>::iterator itr = mst->begin(); itr != mst->end() ; ++itr)
			{
				switch ((*itr)->ownerptr->reType())
				{
				case mnstr:
					dynamic_cast<Monster*>((*itr)->ownerptr)->Controls();
					dynamic_cast<Monster*>((*itr)->ownerptr)->PhysicsInit();
					break;
				case itm:
					dynamic_cast<Item*>((*itr)->ownerptr)->PhysicsInit();
					break;
				case sttc:
					break;
				case ply:
					dynamic_cast<Player*>((*itr)->ownerptr)->Controls();
					dynamic_cast<Player*>((*itr)->ownerptr)->PhysicsInit();
					break;
				case skill:
					dynamic_cast<Skill*>((*itr)->ownerptr)->UpdateMO();
					dynamic_cast<Skill*>((*itr)->ownerptr)->isTimeToDie();
					break;
				}
			}
			std::cout << clkkk.restart().asSeconds() << std::endl;
			*/

			sf::Clock clkkk;
			clkkk.restart().asSeconds();
			for (int i = 0; i < mst->size(); i++)
			{
				switch (mst->at(i)->ownerptr->reType())
				{
				case mnstr:
					dynamic_cast<Monster*>(mst->at(i)->ownerptr)->Controls();
					dynamic_cast<Monster*>(mst->at(i)->ownerptr)->PhysicsInit();
					break;
				case itm:
					dynamic_cast<Item*>(mst->at(i)->ownerptr)->PhysicsInit();
					break;
				case sttc:
					break;
				case ply:
					dynamic_cast<Player*>(mst->at(i)->ownerptr)->Controls();
					dynamic_cast<Player*>(mst->at(i)->ownerptr)->PhysicsInit();
					break;
				case skill:
					dynamic_cast<Skill*>(mst->at(i)->ownerptr)->UpdateMO();
					dynamic_cast<Skill*>(mst->at(i)->ownerptr)->isTimeToDie();
					break;
				}
			}
			std::cout << clkkk.restart().asSeconds() << std::endl;


			QT.CleanTree();

			for (short i = 0; i < mst->size(); i++)
			{
				QT.insert(mst->at(i)->getAABB());
			}

			QT.QueryNodes();
			//QT.tdraw(window);
		}
		ls.setView(window->getView());
		ls.Draw();
		for (short i = 0; i < mst->size(); i++)
		{
			switch (mst->at(i)->ownerptr->reType())
			{
			case mnstr:
				dynamic_cast<Monster*>(mst->at(i)->ownerptr)->draw();
				break;
			case itm:
				dynamic_cast<Item*>(mst->at(i)->ownerptr)->draw();
				break;
			case sttc:
				dynamic_cast<StaticObject*>(mst->at(i)->ownerptr)->draw();
				break;
			case ply:
				dynamic_cast<Player*>(mst->at(i)->ownerptr)->draw();
				break;
			case skill:
				dynamic_cast<Skill*>(mst->at(i)->ownerptr)->draw();
				break;
			}
		}
		EventLoop();
		window->display();
	}
	mst->clear();
}

void GameEngine::Musicfilestream(std::string filename)
{
	std::string buffer;
	std::fstream file;
	file.open(filename);
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	buffer.resize(size);
	file.seekg(0);
	if (file.is_open())
	{
		for (short i = 0; i < size; i++)
			file.get(buffer[i]);
	}
	size_t loc = 0;
	while (loc != std::string::npos)
	{
		loc = buffer.find("Music:", loc);
		if (loc != std::string::npos) 
		{
			size_t end = buffer.find(".wav",loc) + 4;
			std::string fntforward;
			s->SetMusicBuffer(buffer.substr(loc + 6, end - (loc + 6)));
			std::cout << buffer.substr(loc + 6, end - (loc + 6)) << std::endl;
			loc += 1;
		}
	}
	loc = 0;
	while (loc != std::string::npos)
	{
		loc = buffer.find("SFX:", loc);
		if (loc != std::string::npos)
		{
			size_t end = buffer.find(".wav",loc) + 4;
			std::string fntforward;
			s->SetSFXBuffer(buffer.substr(loc + 4, end - (loc + 4)));
			std::cout << buffer.substr(loc + 4, end - (loc + 4)) << std::endl;
			loc += 1;
		}
	}
}

void GameEngine::Graphicsfilestream(std::string filename)
{
	std::string buffer;
	std::fstream file;
	file.open(filename);
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	buffer.resize(size);
	file.seekg(0);
	std::shared_ptr<Textures> GameAssets = Factory::CreatGameAssets();
	if (file.is_open())
	{
		for (short i = 0; i < size; i++)
			file.get(buffer[i]);
	}
	size_t loc = 0;
	while (loc != std::string::npos)
	{
		loc = buffer.find("Asset:", loc);
		if (loc != std::string::npos)
		{
			size_t end = buffer.find(".png", loc) + 4;
			std::string fntforward;
			GameAssets->SetTexturesBuffer(buffer.substr(loc + 6, end - (loc + 6)));
			loc += 1;
		}
	}
}

void GameEngine::EventLoop()
{
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed) {
			Factory::destorylist();
			window->close();
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape)
			{
				if (isPaused == false) {
					theme.pause();
					menu->setView(window->getView());
					menu->Draw();
					isPaused = true;
				}
				else
				{
					theme.play();
					isPaused = false;
				}
			}
		}
		if (event.type == sf::Event::LostFocus)
		{
			theme.pause();
			menu->setView(window->getView());
			menu->Draw();
			isPaused = true;
		}
	}
	if (GameOver == true)
	{
		gomenu->setView(window->getView());
		gomenu->Draw();
		theme.pause();
		sf::Vector2i mpos = sf::Mouse::getPosition();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mpos.x < window->getPosition().x+1080 && mpos.x > window->getPosition().x + 830 && mpos.y < window->getPosition().y + 560 && mpos.y > window->getPosition().y + 450) {
			Factory::destorylist();
			GameOver = false;
			//LoadFromSaveGame();
			theme.play();
		}
		
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mpos.x < window->getPosition().x + 1080 && mpos.x > window->getPosition().x + 830 && mpos.y < window->getPosition().y + 720 && mpos.y > window->getPosition().y + 610) {
			window->close();
		}
	}
	else if (isPaused == true)
	{
		menu->Draw();
		sf::Vector2i mpos = sf::Mouse::getPosition();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mpos.x < window->getPosition().x + 1080 && mpos.x > window->getPosition().x + 830 && mpos.y < window->getPosition().y + 560 && mpos.y > window->getPosition().y + 450) {
			isPaused = false;
			theme.play();
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && mpos.x < window->getPosition().x + 1130 && mpos.x > window->getPosition().x + 920 && mpos.y < window->getPosition().y + 810 && mpos.y > window->getPosition().y + 730) {
			window->close();
		}
	}
}

void GameEngine::LoadFromFile(std::string filename)
{
	std::string buffer;
	std::fstream file;
	file.open(filename);
	short type = 0;
	short mtype = 0;
	size_t loc = 0;
	while (!file.eof()) {
		type = 0;
		mtype = 0;
		std::getline(file, buffer);
		if (buffer.size() < 1)
			break;
		loc = buffer.find("Player:", loc);
		if (loc == std::string::npos) {
			loc = 0;
			loc = buffer.find("Monster:", loc);
		}
		else
		{
			type = ply;
			loc += 7;
		}
		if (loc == std::string::npos) {
			loc = 0;
			loc = buffer.find("Static:", loc);
		}
		else if (type == 0) {
			type = mnstr;
			size_t y = buffer.find("Yeti", loc);
			if (y == std::string::npos)
				mtype = bat;
			else
				mtype = yeti;
			loc += 8;
		}
		if (loc == std::string::npos) {
			loc = 0;
			loc = buffer.find("Item:", loc);
			if (loc != std::string::npos) {
				type = itm;
				loc += 5;
			}
		}
		else if (type == 0)
		{
			type = sttc;
			loc += 7;
		}
		std::string num[4];
		int ac[4];
		for (size_t a = 0; a < 4; a++)
		{
			while (loc != buffer.size() && buffer[loc] != ',') {
				num[a].append(buffer, loc, 1);
				loc++;
			}
			loc++;
			ac[a] = std::stoi(num[a]);
		}
		loc = 0;

		switch (type)
		{
		case ply:
			Factory::SetUpPlyr::SetUpPlayer(ac[0], ac[1], ac[2], ac[3], 100, 5, 5, window, "bnn.png");
			Factory::CreatePlayer();
			break;
		case sttc:
			Factory::SetUpStatic::SetUpStaticObject(ac[0], ac[1], ac[2], ac[3], window,"steel.png");
			Factory::CreatestaticObject();
			break;
		case mnstr:
			Factory::SetUpMstr::SetUpMonster(ac[0], ac[1], ac[2], ac[3], 100, 5, 5, window);
			switch (mtype)
			{
			case yeti:
				Factory::SetUpMstr::SetUpYeti(2, "yeti.png");
				Factory::CreateMonster("Yeti");
				break;
			case bat:
				Factory::SetUpMstr::SetUpBat(ac[1], 2, "bat.png");
				Factory::CreateMonster("Bat");
				break;
			}
			break;
		case itm:
			Factory::SetUpItm::SetUpItem(ac[0], ac[1], ac[2], ac[3], window, "coinsprite.png");
			Factory::CreateItem();
			break;

		}
	}
}



GameEngine::~GameEngine()
{
}
