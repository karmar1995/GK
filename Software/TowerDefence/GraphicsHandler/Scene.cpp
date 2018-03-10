#include "Scene.h"
#include "GraphicManager.h"

Scene::Scene(): squareArray(sf::Quads)
{
}

void Scene::load(const Map& map)
{
	GraphicManager &cfg = GraphicManager::getInstance();
	squareArray.resize(cfg.getWidth()*cfg.getHeigth() * 4);
	sf::Vertex *square;
	for (int i = 0; i < cfg.getWidth(); i++)
	{
		for (int j = 0; j < cfg.getHeigth(); j++)
		{
			square = &squareArray[(j*cfg.getWidth() + i) * 4];
			//set square coordinates
			square[0].position = sf::Vector2f(i*cfg.getSquareWidth(), j*cfg.getSquareHeigth());
			square[1].position = sf::Vector2f((i+1)*cfg.getSquareWidth(), j*cfg.getSquareHeigth());
			square[2].position = sf::Vector2f((i+1)*cfg.getSquareWidth(), (j+1)*cfg.getSquareHeigth());
			square[3].position = sf::Vector2f(i*cfg.getSquareWidth(), (j+1)*cfg.getSquareHeigth());
			//choose texture
			sf::Rect<float> texPosition;
			switch (map.GetSquare(i, j))
			{
			case TT_EMPTY:
				texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_EMPTY);
				break;
			case TT_PATH:
				texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_PATH);
				break;
			case TT_TOWER:
				texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_TOWER);
				break;
			default:
				texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_ERROR);
				break;
			}
			//set texture
			square[0].texCoords = sf::Vector2f(texPosition.left, texPosition.top);
			square[1].texCoords = sf::Vector2f(texPosition.left+texPosition.width, texPosition.top);
			square[2].texCoords = sf::Vector2f(texPosition.left+texPosition.width, texPosition.top+texPosition.height);
			square[3].texCoords = sf::Vector2f(texPosition.left, texPosition.top+texPosition.height);
		}
	}
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = GraphicManager::getInstance().getTexture();
	target.draw(squareArray, states);
}


Scene::~Scene()
{
}
