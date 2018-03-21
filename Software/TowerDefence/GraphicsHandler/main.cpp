#ifndef WIN32
#include <SFML/Graphics.hpp>
#endif
#include <iostream>
#include <cstdlib>
#include "Scene.h"
#include "GraphicManager.h"
#include "TowerManager.h"
#include "TowerGraphic.h"

int main(int argc, char** argv)
{
#ifndef WIN32
	try {
		GraphicManager::getInstance().setResolution(500, 260);
	}
	catch (std::runtime_error e) {
		std::cerr << e.what() <<std::endl;
	}

	sf::RenderWindow window(sf::VideoMode(
		GraphicManager::getInstance().getResolutionX(), 
		GraphicManager::getInstance().getResolutionY()), 
		"SFML works!");

	//load scene from a map
	Scene scene;
	Map map;
	try
	{
		MapFileParser parser("Map.txt");
		map = parser.parsedMap();
		GraphicManager::getInstance().setSize(map.GetWidth(), map.GetHeight());
		scene.load(map);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	TowerManager tm(map);
	TowerGraphic towers;
	towers.load(tm);

	while (window.isOpen())
	{
		//window.
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
					if (tm.buy(mouseCoords.x, mouseCoords.y))
					{
						towers.load(tm);
					}
					else if (tm.isTower(mouseCoords.x, mouseCoords.y))
					{
						tm.upgrade(mouseCoords.x, mouseCoords.y);
						towers.load(tm);
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (tm.isTower(mouseCoords.x, mouseCoords.y))
					{
						tm.sell(mouseCoords.x, mouseCoords.y);
						towers.load(tm);
					}
				}
			}
		}

		window.clear();
		window.draw(scene);
		window.draw(towers);
		window.display();
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