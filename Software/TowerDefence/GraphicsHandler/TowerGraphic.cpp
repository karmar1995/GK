#include "TowerGraphic.h"
#include "GraphicManager.h"


TowerGraphic::TowerGraphic():towerArray(sf::Quads)
{
}

void TowerGraphic::load(const TowerManager& tm)
{
	GraphicManager &cfg = GraphicManager::getInstance();
	towerArray.resize(tm.getSize() * 4);
	sf::Vertex *square;
	int i = 0;
	for (auto it = tm.begin(); it != tm.end(); ++it, ++i)
	{
		square = &towerArray[i * 4];
		//set square coordinates
		square[0].position = sf::Vector2f(it->getX()*cfg.getSquareWidth(), it->getY()*cfg.getSquareHeigth());
		square[1].position = sf::Vector2f((it->getX() + 1)*cfg.getSquareWidth(), it->getY()*cfg.getSquareHeigth());
		square[2].position = sf::Vector2f((it->getX() + 1)*cfg.getSquareWidth(), (it->getY() + 1)*cfg.getSquareHeigth());
		square[3].position = sf::Vector2f(it->getX()*cfg.getSquareWidth(), (it->getY() + 1)*cfg.getSquareHeigth());
		//choose texture
		sf::Rect<float> texPosition = cfg.getTextureCoordinates(
			GraphicManager::TextureIndex(cfg.TextureIndex::TI_TOWER1+it->getLevel()));
		//set texture
		square[0].texCoords = sf::Vector2f(texPosition.left, texPosition.top);
		square[1].texCoords = sf::Vector2f(texPosition.left + texPosition.width, texPosition.top);
		square[2].texCoords = sf::Vector2f(texPosition.left + texPosition.width, texPosition.top + texPosition.height);
		square[3].texCoords = sf::Vector2f(texPosition.left, texPosition.top + texPosition.height);
	}
}

void TowerGraphic::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = GraphicManager::getInstance().getTexture();
	target.draw(towerArray, states);
}

TowerGraphic::~TowerGraphic()
{
}
