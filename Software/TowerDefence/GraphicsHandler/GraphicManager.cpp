#include "GraphicManager.h"

///
///@brief Gets GraphicManager object
///
///If the object doesn't exist and it can't be created, runtimr_error is thrown
///@returns instance of GraphicManager
///
GraphicManager& GraphicManager::getInstance()
{
	static GraphicManager instance;
	return instance;
}

///
///@brief Gets window width in squares
///@returns window width
///
unsigned int GraphicManager::getWidth()
{
	return width;
}

///
///@brief Gets window heigth in squares
///@returns window heigth
///
unsigned int GraphicManager::getHeigth()
{
	return heigth;
}

///
///@brief Gets window width in pixels
///@returns window width
///
unsigned int GraphicManager::getResolutionX()
{
	return resolutionX;
}

///
///@brief Gets window heigth in pixels
///@returns window heigth
///
unsigned int GraphicManager::getResolutionY()
{
	return resolutionY;
}

///
///@brief Gets width of single square on window
///@returns square width in pixels
///@returns 0 if window width is not set
///@note returned value is of double type, not integer
///
double GraphicManager::getSquareWidth()
{
	if(width!=0)
		return (double)resolutionX/width;
	return 0;
}

///
///@brief Gets heigth of single square on window
///@returns square heigth in pixels
///@returns 0 if window heigth is not set
///@note returned value is of double type, not integer
///
double GraphicManager::getSquareHeigth()
{
	if (heigth != 0)
		return (double)resolutionY / heigth;
	return 0;
}

///
///@brief Sets size of window in squares
///@param x width of window
///@param y height of window
///
void GraphicManager::setSize(unsigned int x, unsigned  int y)
{
	width = x;
	heigth = y;
}

///
///@brief Sets size of window in pixels
///@param x width of window
///@param y height of window
///
void GraphicManager::setResolution(unsigned int x, unsigned  int y)
{
	resolutionX = x;
	resolutionY = y;
}

///
///@brief Gets coordinates of a texture in tileset
///
///Gets position of texture indicated by argument in texture atlas coordinates
///@param i selected texture index
///@returns rectangle reresenting coords of top left texture corner and its size
///
sf::Rect<float> GraphicManager::getTextureCoordinates(TextureIndex i)
{
	sf::Rect<float> answer;
	answer.left = (i *tileWidth) % tileset.getSize().x+1;
	answer.top = i / (tileset.getSize().x / tileWidth) *tileHeigth+1;
	answer.height = tileHeigth-2;
	answer.width = tileWidth-2;
	return answer;
}

///
///@brief Gets texture atlas object
///@returns texture atlas
///
const sf::Texture * GraphicManager::getTexture()
{
	return &tileset;
}

///
///@brief Gets font object
///@returns font
///
sf::Font & GraphicManager::getFont()
{
	return font;
}

///
///@brief Default constructor
///
///Creates and initialises instance of GraphicManager \n
///Size is set to 0 by default, texture atlas and font are loaded
///@throws runtime_error if texture atlas or font cannot be loaded
///
GraphicManager::GraphicManager(): width(0), heigth(0), resolutionX(0), resolutionY(0)
{
	sf::Image image;
	if(!image.loadFromFile(texFile))
		throw std::runtime_error("Unable to open texture file");
	image.createMaskFromColor(sf::Color(255, 0, 255));
	tileset.loadFromImage(image);
	tileset.setSmooth(true);
	if(!font.loadFromFile("times.ttf"))
		throw std::runtime_error("Unable to open font");
}

///
///@brief Destructor
///
GraphicManager::~GraphicManager()
{
}
