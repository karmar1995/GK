#include "GameplayHandler.h"



GameplayHandler::GameplayHandler()
{
	m_Window.create(sf::VideoMode(
		GraphicManager::getInstance().getResolutionX(),
		GraphicManager::getInstance().getResolutionY()),
		"Tower defence");
	m_CurrentMap = MapFiles[0];
	m_Valid = ParseMap();
	if (m_Valid)
	{
		m_TowerManager = new TowerManager(*m_Map);
		m_Scene = new Scene(*m_Map);
		m_Scene->setTowers(m_TowerManager); 
		PushEnemies();
	}

}


void GameplayHandler::MainLoop()
{
	while (m_Window.isOpen())
	{
		sf::Event event;
		for (auto enemy : m_EnemyVector)
			m_Scene->PushObject(enemy);
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				m_Window.close();
			if (event.type == sf::Event::MouseButtonReleased)
			{
				auto mouseCoords = m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
				mouseCoords.x /= GraphicManager::getInstance().getSquareWidth();
				mouseCoords.y /= GraphicManager::getInstance().getSquareHeigth();
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (!m_TowerManager->buy(mouseCoords.x, mouseCoords.y))
					{
						if (m_TowerManager->isTower(mouseCoords.x, mouseCoords.y))
						{
							m_TowerManager->upgrade(mouseCoords.x, mouseCoords.y);
						}
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (m_TowerManager->isTower(mouseCoords.x, mouseCoords.y))
					{
						m_TowerManager->sell(mouseCoords.x, mouseCoords.y);
					}
				}
			}
		}
		TowerManager manager = *m_TowerManager;
		for (int i = 0; i < m_TowerManager->getSize(); i++)
		{
			for (auto enemy : m_Scene->GetMoveableObjects())
			{
				EnemyDesigner* toShot = dynamic_cast<EnemyDesigner*>(enemy);
				if (toShot)
				{
					if (auto bullet = manager[i].fire(toShot, *m_Scene))
					{
						m_Scene->PushObject(bullet);
					}
				}
			}
		}
		m_Window.clear();
		m_Scene->UpdateScene();
		m_Window.draw(*m_Scene);
		m_Window.display();
		m_Scene->Cleanup();
	}
}

GameplayHandler::~GameplayHandler()
{
	ReleaseResources();
}

void GameplayHandler::ReleaseResources()
{
	if (m_Map)
	{
		delete m_Map;
		m_Map = nullptr;
	}
	if (m_TowerManager)
	{
		delete m_TowerManager;
		m_TowerManager = nullptr;
	}
	if (m_Scene)
	{
		delete m_Scene;
		m_Scene = nullptr;
	}
}

bool GameplayHandler::ParseMap()
{
	try
	{
		MapFileParser parser(m_CurrentMap);
		m_Map = new Map(parser.parsedMap());
	}
	//TODO : Handle custom exception
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return false;
	}
	return true;
}

void GameplayHandler::PushEnemies()
{
	Point startPoint = m_Map->GetPoint(0, 0);
	m_EnemyVector.push_back(new Snake(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 60)));
//	m_EnemyVector.push_back(new Snake(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 60)));
//	m_EnemyVector.push_back(new Snake(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 60)));
//	m_EnemyVector.push_back(new Snake(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 60)));
//	m_EnemyVector.push_back(new Zombie(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 27), sf::Color::Red, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Zombie(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 27), sf::Color::Red, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Zombie(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 27), sf::Color::Red, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Bird(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Bird(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Bird(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Bird(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Bird(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 0)));
//	m_EnemyVector.push_back(new Vampire(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(12, 16), sf::Color::Yellow, sf::Vector2f(0, 16)));
//	m_EnemyVector.push_back(new Vampire(m_Scene->getSquareOrigin(startPoint), sf::Vector2f(12, 16), sf::Color::Yellow, sf::Vector2f(0, 16)));
}
