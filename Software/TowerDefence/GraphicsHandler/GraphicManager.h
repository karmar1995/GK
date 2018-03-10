#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class GraphicManager
{
public:
	enum TextureIndex { TI_EMPTY, TI_PATH, TI_TOWER, TI_ERROR=99 };

	static GraphicManager& getInstance();

	//Getters for window parameters
	unsigned int getWidth();			//in squares
	unsigned int getHeigth();			//in squares
	unsigned int getResolutionX();		//in pixels
	unsigned int getResolutionY();		//in pixels
	unsigned int getSquareWidth();		//in pixels
	unsigned int getSquareHeigth();		//in pixels

	//Setters for window parameters
	void setSize(unsigned int x, unsigned int y);			//in squares
	void setResolution(unsigned int x, unsigned int y);		//in pixels

	//Texture getters
	sf::Rect<float> getTextureCoordinates(TextureIndex i);
	const sf::Texture* getTexture();

	private:
	GraphicManager();
	virtual ~GraphicManager();

	//window parameters
	unsigned int width;
	unsigned int heigth;
	unsigned int resolutionX;
	unsigned int resolutionY;

	//textures with parameters
	sf::Texture tileset;
	const unsigned int tileHeigth=32;
	const unsigned int tileWidth=32;
	const std::string texFile = "texture_atlas.bmp";
};

