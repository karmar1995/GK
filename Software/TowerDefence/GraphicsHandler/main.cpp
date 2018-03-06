#ifndef WIN32
#include <SFML/Graphics.hpp>
#endif
#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
#ifndef WIN32
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
#endif
#ifdef WIN32
	std::cout << "Unable to build WIN32 application yet, please use x64 configuration. " << std::endl;
	system("pause");
#endif
	return 0;
}