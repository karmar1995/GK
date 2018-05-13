#ifndef WIN32
#include <SFML/Graphics.hpp>
#endif
#include <iostream>
#include <cstdlib>
#include "Scene.h"
#include "GraphicManager.h"
#include "EnemyDesigner.h"
#include "TowerManager.h"
#include <Windows.h>
#include "TowerGraphic.h"
#include "BulletDesigner.h"
#include "GameStatistics.h"
#include "ConfigurationManager.h"
#include "GameplayHandler.h"

std::vector<EnemyDesigner*> ParseEnemiesWave(const Scene& scene, const std::vector<std::tuple <int, EnemyDesigner*, std::string>>& enemiesVector)
{
	std::vector<EnemyDesigner*> retVal;
	for (auto it : enemiesVector)
	{
		int number = std::get<0>(it);
		std::string type = std::get<2>(it);
		for (int i = 0; i < number; i++)
		{
			if(type == "bird")
			{
				retVal.push_back(new Bird(scene.getSquareOrigin(Point(0, 0)), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 0)));
			}
			if (type == "zombie")
			{
				retVal.push_back(new Zombie(scene.getSquareOrigin(Point(0, 0)), sf::Vector2f(20, 27), sf::Color::Red, sf::Vector2f(0, 0)));
			}
			if (type == "snake")
			{
				retVal.push_back(new Snake(scene.getSquareOrigin(Point(0,0)), sf::Vector2f(20, 20), sf::Color::Blue, sf::Vector2f(0, 60)));
			}
			if (type == "vampire")
			{
				retVal.push_back(new Vampire(scene.getSquareOrigin(Point(0, 0)), sf::Vector2f(12, 16), sf::Color::Yellow, sf::Vector2f(0, 16)));
			}
		}
	}
	return retVal;
}

int main(int argc, char** argv)
{
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

	GameStatistics gm;
	gm.loadFromFile("statistics.txt");
	gm.updateStatistics(true);
	gm.saveToFile("statistics.txt");
	ConfigurationManager confMng;
	confMng.readConfiguration();
	int lives = 100;
	int lvl = 0;
	int wave = 0;
	try
	{
		MapFileParser parser("Testcases\\Map.txt");
		Map m = parser.parsedMap();
		Scene scene(m);
		TowerManager tm(m);
		scene.setTowers(&tm);
		sf::Vector2f mouseCoords;
		sf::Text info;
		
		info.setFillColor(sf::Color::Black);
		info.setFont(GraphicManager::getInstance().getFont());
		info.setCharacterSize(12);
		while (window.isOpen())
		{
			bool loadNewWave = scene.EndOfWave();
			if (loadNewWave)
			{
				std::vector<EnemyDesigner*> enemies;
				if (lvl < confMng.getLevels().size())
				{
					Level curLvl = confMng.getLevels()[lvl];
					if (wave < curLvl.getWaves().size())
					{
						Wave curWave = curLvl.getWaves()[wave];
						enemies = ParseEnemiesWave(scene, curWave.getEnemiesVector());
						wave++;
					}
					else
					{
						wave = 0;
						lvl++;
					}
				}
				for (auto enemy : enemies)
				{
					scene.PushObject(enemy);
				}
				if (lvl == confMng.getLevels().size())
				{
					MessageBox(window.getSystemHandle(), LPCWSTR(L"You win"), LPCWSTR(L"WINNER"), MB_OK);
					window.close();
					return 0;
				}
			}
			lives -= scene.EnemyAtEnd();
			sf::Text livesDsp;
			livesDsp.setFillColor(sf::Color::Black);
			livesDsp.setFont(GraphicManager::getInstance().getFont());
			livesDsp.setCharacterSize(24);
			livesDsp.setString("Lives: " + std::to_string(lives));
			livesDsp.setPosition(window.getSize().x - 125, 20);
			if (lives < 0)
			{
				MessageBox(window.getSystemHandle(), LPCWSTR(L"You loose"), LPCWSTR(L"LOOSER"), MB_OK);
				window.close();
				return 0;
			}
			mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
			info.setPosition(mouseCoords.x+10, mouseCoords.y+10);
			mouseCoords.x /= GraphicManager::getInstance().getSquareWidth();
			mouseCoords.y /= GraphicManager::getInstance().getSquareHeigth();
			if (scene.getMap().GetPoint(mouseCoords.x, mouseCoords.y).GetTerrainType() != Point::TT_PATH)
			{
				if (tm.isTower(mouseCoords.x, mouseCoords.y))
				{
					Tower tower = tm.get(mouseCoords.x, mouseCoords.y);
					info.setString("Level: " + std::to_string(tower.getLevel()) 
						+ (tower.getLevel()<tower.getMaxLevel() ?"\nUpgrade: " + std::to_string(tower.upgradePrice()) + "$" : "")
						+ "\nSell: " + std::to_string(tower.getPrice()) + "$");
				}
				else
				{
					info.setString("Buy: " + std::to_string(Tower::getPrice()) + "$");
				}
			}
			else
			{
				info.setString("");
			}
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonReleased)
				{
					mouseCoords = window.mapPixelToCoords(sf::Mouse::getPosition(window));
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
			window.draw(info);
			window.draw(livesDsp);
			window.display();
			scene.Cleanup();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}