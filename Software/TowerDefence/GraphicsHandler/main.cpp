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

	sf::RenderWindow window(sf::VideoMode(
		GraphicManager::getInstance().getResolutionX(), 
		GraphicManager::getInstance().getResolutionY()), 
		"SFML works!");
	//load scene from a map
	try
	{
		MapFileParser parser("Testcases\\Map.txt");
		Map m = parser.parsedMap();
		Scene scene(m);

		TowerManager tm(m);
		scene.setTowers(&tm);
		int licznik = 0;
		EnemyBase enemy(m.GetPoint(1,1), Statistics(1, 1, 1));
		EnemyBase enemy2(m.GetPoint(0,0), Statistics(1, 1, 1));
		EnemyDesigner* tmp = new EnemyDesigner(enemy, scene.getSquareOrigin(enemy.getPosition()), sf::Vector2f(10, 5), sf::Color::Red, sf::Vector2f(0, 0));
		EnemyDesigner* tmp2 = new EnemyDesigner(enemy2, scene.getSquareOrigin(enemy2.getPosition()), sf::Vector2f(10, 5), sf::Color::Red, sf::Vector2f(0, 0));
		scene.PushObject(tmp);
		scene.PushObject(tmp2);
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
				if (auto bullet = tm[i].fire(tmp, scene))
				{
					scene.PushObject(bullet);
				}
			}
			scene.Cleanup();
			window.clear();
			scene.UpdateScene();
			window.draw(scene);
			window.display();
		}
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