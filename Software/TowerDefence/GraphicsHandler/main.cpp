#ifndef WIN32
#include <SFML/Graphics.hpp>
#endif
#include <iostream>
#include <cstdlib>
#include "Scene.h"
#include "GraphicManager.h"
#include "EnemyDesigner.h"
#include "TowerManager.h"
#include "TowerGraphic.h"
#include "BulletDesigner.h"
#include "GameStatistics.h"
#include "ConfigurationManager.h"
#include "GameplayHandler.h"
int main(int argc, char** argv)
{
#ifndef WIN32
	try {
		GraphicManager::getInstance().setResolution(500, 260);
	}
	catch (std::runtime_error e) {
		std::cerr << e.what() << std::endl;
	}
	srand(time(NULL));
	GraphicManager::getInstance().setResolution(500, 260);
	GraphicManager::getInstance().setSize(20, 20);

//	GameplayHandler handler;
//	handler.MainLoop();
	//load scene from a map
	
	sf::RenderWindow window(sf::VideoMode(
	GraphicManager::getInstance().getResolutionX(),
	GraphicManager::getInstance().getResolutionY()),
	"SFML works!");

	GameStatistics gm;
	gm.loadFromFile("statistics.txt");
	gm.updateStatistics(true);
	gm.saveToFile("statistics.txt");
	ConfigurationManager confMng;
	confMng.readConfiguration();


	try
	{
		MapFileParser parser("Testcases\\Map.txt");
		Map m = parser.parsedMap();
		Scene scene(m);

		TowerManager tm(m);
		scene.setTowers(&tm);
		EnemyBase enemy(m.GetPoint(1,1), 1,1,1);
		EnemyBase enemy2(m.GetPoint(0,0),1,1,1);
		EnemyBase enemy3(m.GetPoint(3,3),1,1,1);
		EnemyDesigner* tmp = new Snake(scene.getSquareOrigin(enemy.getPosition()), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 60));
		Zombie* tmp2 = new Zombie(scene.getSquareOrigin(enemy2.getPosition()), sf::Vector2f(20, 27), sf::Color::Red, sf::Vector2f(0, 0));
		Bird* tmp3 = new Bird( scene.getSquareOrigin(enemy.getPosition()), sf::Vector2f(20,20), sf::Color::Blue, sf::Vector2f(0, 0));
		Vampire* tmp4 = new Vampire(scene.getSquareOrigin(enemy2.getPosition()), sf::Vector2f(12, 16), sf::Color::Yellow, sf::Vector2f(0, 16));


		scene.PushObject(tmp);
		scene.PushObject(tmp2);
		scene.PushObject(tmp3);
		scene.PushObject(tmp4);
		
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonReleased)
				{
					auto mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
					mouseCoords.x /= GraphicManager::getInstance().getSquareWidth();
					mouseCoords.y /= GraphicManager::getInstance().getSquareHeigth();
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						if (!tm.buy(mouseCoords.x, mouseCoords.y))
						{
							if (tm.isTower(mouseCoords.x, mouseCoords.y))
							{
								tm.upgrade(mouseCoords.x, mouseCoords.y);
							}
						}
					}
					else if (event.mouseButton.button == sf::Mouse::Right)
					{
						if (tm.isTower(mouseCoords.x, mouseCoords.y))
						{
							tm.sell(mouseCoords.x, mouseCoords.y);
						}
					}
				}
			}
			for (int i = 0; i < tm.getSize();i++)
			{
				for (auto enemy : scene.GetMoveableObjects())
				{
					EnemyDesigner* toShot = dynamic_cast<EnemyDesigner*>(enemy);
					if (toShot)
					{
						if (auto bullet = tm[i].fire(toShot, scene))
						{
							scene.PushObject(bullet);
						}
					}
				}
			}
			window.clear();
			scene.UpdateScene();
			window.draw(scene);
			window.display();
			scene.Cleanup();
		}
		delete tmp;
		delete tmp2;
		delete tmp3;
		delete tmp4;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

#endif
#ifdef WIN32
	std::cout << "Unable to build WIN32 application yet, please use x64 configuration. " << std::endl;
	system("pause");
#endif
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}