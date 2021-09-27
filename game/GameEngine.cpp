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
	
	isPaused = false;
	ElapsedTime = 0;
}

void GameEngine::GameLoop()
{
	frameClock.restart();
	std::vector<std::shared_ptr<Object>> *mst;
	mst = Factory::callobjectList();
	//window->setFramerateLimit(60);

	LoadFromFile("Map.txt");
	QuadTree QT(mst->at(0)->GetTL().GetX() - 1000, -10800, mst->at(mst->size() - 1)->GetTL().GetX() + 1000, 10800);

	Physics::GravityOn();

	sf::Vector2f a(0, 0);
	Graphics ls(a, "Background.png", window, nullptr);
	
	while (window->isOpen())
	{
		run(&QT, mst, &ls);
	}
	mst->clear();
}

void GameEngine::run(QuadTree * QT, std::vector<std::shared_ptr<Object>> *mst, Graphics *ls)
{
	window->clear();
	if (isPaused == false && GameOver == false) {
		Running(QT, mst);
	}
	Operate(mst,QT,ls);
}

void GameEngine::Running(QuadTree * QT, std::vector<std::shared_ptr<Object>>* mst)
{
	EndOrDestory(mst);
	ElapsedTime = frameClock.getElapsedTime().asMilliseconds();
	if (ElapsedTime > 15) {
		ActivateObjects(mst);
		frameClock.restart();
	}
	
	QT->CleanTree();
	InsertObjectsToQuadTree(QT, mst);
	QT->QueryNodes();
	QT->tdraw(*window);
}

void GameEngine::EndOrDestory(std::vector<std::shared_ptr<Object>>* mst)
{
	for (short i = 0; i < mst->size(); i++)
	{
		bool ti = mst->at(i)->isUpForDestruction();
		if (ti) {
			if (mst->at(i)->reType() == ply)
				GameOver = true;
			Factory::destoryObject(i);
		}
	}
}

void GameEngine::Operate(std::vector<std::shared_ptr<Object>>* mst, QuadTree * QT, Graphics *ls)
{
		window->clear();
		DrawAllObjects(mst,ls);
		EventLoop();
		window->display();
}

void GameEngine::ActivateObjects(std::vector<std::shared_ptr<Object>>* mst)
{
	for (int i = 0; i < mst->size(); i++)
	{
		mst->at(i)->action();
	}
}

void GameEngine::InsertObjectsToQuadTree(QuadTree * QT, std::vector<std::shared_ptr<Object>>* mst)
{
	for (short i = 0; i < mst->size(); i++)
	{
		std::shared_ptr<AABB> ab = std::dynamic_pointer_cast<AABB>(mst->at(i));
		QT->insert(ab.get());
	}
}

void GameEngine::DrawAllObjects(std::vector<std::shared_ptr<Object>>* mst, Graphics *ls)
{
	ls->setView(window->getView());
	ls->Draw();
	for (short i = 0; i < mst->size(); i++)
	{
		mst->at(i)->draw();
	}
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
