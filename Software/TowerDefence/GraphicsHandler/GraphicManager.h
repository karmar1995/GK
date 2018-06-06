#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Map.hpp"

///
///@brief Singleton class managing window parameters and textures
///
class GraphicManager
{
public:
	///@brief Enumeration of texture tiles
	///
	enum TextureIndex { TI_EMPTY, TI_PATH, TI_TOWER1=0x10, TI_ERROR=0xff };

	static GraphicManager& getInstance();

	//Getters for window parameters
	unsigned int getWidth();			//in squares
	unsigned int getHeigth();			//in squares
	unsigned int getResolutionX();		//in pixels
	unsigned int getResolutionY();		//in pixels
	double getSquareWidth();			//in pixels
	double getSquareHeigth();			//in pixels

	//Setters for window parameters
	void setSize(unsigned int x, unsigned int y);			//in squares
	void setResolution(unsigned int x, unsigned int y);		//in pixels

	//Texture getters
	sf::Rect<float> getTextureCoordinates(TextureIndex i);
	const sf::Texture* getTexture();
	
	sf::Font & getFont();

	private:
	GraphicManager();
	virtual ~GraphicManager();

	//window parameters
	unsigned int width;				///<Window width in tiles
	unsigned int heigth;			///<Window heigth in tiles
	unsigned int resolutionX;		///<Window width in pixels
	unsigned int resolutionY;		///<Window heigth in pixels

	//textures with parameters
	sf::Texture tileset;					///<Atlas of all texture tiles
	const unsigned int tileHeigth=32;		///<Tile heigth
	const unsigned int tileWidth=32;		///<Tile width
	const std::string texFile = "texture_atlas.bmp";	///<Name of texture atlas file

	sf::Font font;					///<Font used in game
};

