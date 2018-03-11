#include "GraphicManager.h"

GraphicManager& GraphicManager::getInstance()
{
	static GraphicManager instance;
	return instance;
}

unsigned int GraphicManager::getWidth()
{
	return width;
}

unsigned int GraphicManager::getHeigth()
{
	return heigth;
}

unsigned int GraphicManager::getResolutionX()
{
	return resolutionX;
}

unsigned int GraphicManager::getResolutionY()
{
	return resolutionY;
}

unsigned int GraphicManager::getSquareWidth()
{
	if(width!=0)
		return resolutionX/width;
	return 0;
}

unsigned int GraphicManager::getSquareHeigth()
{
	if (heigth != 0)
		return resolutionY / heigth;
	return 0;
}

void GraphicManager::setSize(unsigned int x, unsigned  int y)
{
	width = x;
	heigth = y;
}

void GraphicManager::setResolution(unsigned int x, unsigned  int y)
{
	resolutionX = x;
	resolutionY = y;
}

sf::Rect<float> GraphicManager::getTextureCoordinates(TextureIndex i)
{
	sf::Rect<float> answer;
	answer.left = (i *tileWidth) % tileset.getSize().x+1;
	answer.top = i / (tileset.getSize().x / tileWidth) *tileHeigth+1;
	answer.height = tileHeigth-2;
	answer.width = tileWidth-2;
	return answer;
}

const sf::Texture * GraphicManager::getTexture()
{
	return &tileset;
}

GraphicManager::GraphicManager(): width(0), heigth(0), resolutionX(0), resolutionY(0)
{
	if (!tileset.loadFromFile(texFile))
		throw std::runtime_error("Unable to open texture file");
	tileset.setSmooth(true);
}


GraphicManager::~GraphicManager()
{
}