#include "Scene.h"
#include "GraphicManager.h"
#include "EnemyDesigner.h"
#include <vector>

Scene::Scene(Map map): squareArray(sf::Quads), m_Map(map)
{
	load();
}

void Scene::load()
{
	GraphicManager &cfg = GraphicManager::getInstance();
	squareArray.resize(cfg.getWidth()*cfg.getHeigth() * 4);
	sf::Vertex *square;
	for (uint i = 0; i < cfg.getWidth(); i++)
	{
		for (uint j = 0; j < cfg.getHeigth(); j++)
		{
			square = &squareArray[(j*cfg.getWidth() + i) * 4];
			//set square coordinates
			square[0].position = sf::Vector2f(i*cfg.getSquareWidth(), j*cfg.getSquareHeigth());
			square[1].position = sf::Vector2f((i+1)*cfg.getSquareWidth(), j*cfg.getSquareHeigth());
			square[2].position = sf::Vector2f((i+1)*cfg.getSquareWidth(), (j+1)*cfg.getSquareHeigth());
			square[3].position = sf::Vector2f(i*cfg.getSquareWidth(), (j+1)*cfg.getSquareHeigth());
			//choose texture
			sf::Rect<float> texPosition;
			if (m_Map.IsInMap(i, j))
			{
				switch (m_Map.GetPoint(i, j).GetTerrainType())
				{
				case Point::TerrainType::TT_EMPTY:
					texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_EMPTY);
					break;
				case Point::TerrainType::TT_PATH:
					texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_PATH);
					break;
				case Point::TerrainType::TT_TOWER:
					texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_TOWER1);
					break;
				default:
					texPosition = cfg.getTextureCoordinates(cfg.TextureIndex::TI_ERROR);
					break;
				}
			}
			//set texture
			square[0].texCoords = sf::Vector2f(texPosition.left, texPosition.top);
			square[1].texCoords = sf::Vector2f(texPosition.left+texPosition.width, texPosition.top);
			square[2].texCoords = sf::Vector2f(texPosition.left+texPosition.width, texPosition.top+texPosition.height);
			square[3].texCoords = sf::Vector2f(texPosition.left, texPosition.top+texPosition.height);
		}
	}
}



void Scene::UpdateScene()
{
	tm->updateGraphic(towers);
	std::vector<IMoveable*> tmp;
	for (IMoveable* moveable : m_MoveableObjects)
	{
		for (int i = 0; i < tm->getSize(); i++)
		{
			EnemyDesigner* enemy = dynamic_cast<EnemyDesigner*>(moveable);
			if (enemy)
			{
				if (auto bullet = tm->operator[](i).fire(enemy, *this))
				{
					tmp.push_back(bullet);
				}
			}
		}
		moveable->Move(m_Map, *this);
		for (IMoveable* other : m_MoveableObjects)
		{
			if(moveable!=other)
				if (moveable->Collides(other))
				{
					moveable->Collision(other);
					break;
				}
		}
	}
	for (IMoveable* moveable : m_MoveableObjects)
	{
		EnemyDesigner* enemy = dynamic_cast<EnemyDesigner*>(moveable);
		if (enemy && enemy->Removeable())
		{
			tm->AddCash(enemy->GetValue());
		}
	}
	for (IMoveable *obj : tmp)
		PushObject(obj);
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	states.texture = GraphicManager::getInstance().getTexture();
	target.draw(squareArray, states);
	towers.draw(target, states);
	for (IMoveable* moveable : m_MoveableObjects)
	{
		moveable->draw(target, states);
	}
	sf::Text cashText("Cash: " + tm->GetCash(),GraphicManager::getInstance().getFont(),24);
	cashText.setFillColor(sf::Color(0, 0, 0));
	cashText.setPosition(target.getView().getSize().x - 100, 0);
	target.draw(cashText, states);
}
sf::Vector2f Scene::getSquareOrigin(Point p) const
{
	GraphicManager &cfg = GraphicManager::getInstance();
	const sf::Vertex* square = &squareArray[(p.GetY() * cfg.getWidth() + p.GetX()) * 4];
	sf::Vector2f top_left = square[0].position;
	sf::Vector2f bot_right = square[2].position;
	return sf::Vector2f((bot_right.x + top_left.x) / 2, (bot_right.y + top_left.y) / 2);
}

const Map & Scene::getMap() const
{
	return m_Map;
}

void Scene::Cleanup()
{
	MoveableVector newVector;
	std::copy_if(m_MoveableObjects.begin(), m_MoveableObjects.end(), std::back_inserter(newVector), 
		[](IMoveable* toCopy) 
	{
		if ((toCopy->Removeable()))
		{
			delete toCopy;
			toCopy = nullptr;
			return false;
		}
		return true; 
	});
	
	m_MoveableObjects.clear();
	m_MoveableObjects = newVector;
}

void Scene::setTowers(TowerManager *tower)
{
	this->tm = tower;
	towers.load(*tm);
}

MoveableVector Scene::GetMoveableObjects()
{
	return m_MoveableObjects;
}


Scene::~Scene()
{
}

void Scene::PushObject(IMoveable * obj)
{
	m_MoveableObjects.push_back(obj);
}

void Scene::DeleteObject(IMoveable * obj)
{
	
}
