#ifndef WIN32
#include <SFML/Graphics.hpp>
#endif
#include <iostream>
#include <cstdlib>
#include "Scene.h"
#include "GraphicManager.h"

int main(int argc, char** argv)
{
#ifndef WIN32
	
	GraphicManager::getInstance().setResolution(500, 260);
	GraphicManager::getInstance().setSize(20, 20);

	sf::RenderWindow window(sf::VideoMode(
		GraphicManager::getInstance().getResolutionX(), 
		GraphicManager::getInstance().getResolutionY()), 
		"SFML works!");

	//load scene from a map
	Scene scene;
	MapFileParser parser("Map.txt");
	try
	{
		Map m = parser.parsedMap();
		scene.load(m);
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(scene);
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