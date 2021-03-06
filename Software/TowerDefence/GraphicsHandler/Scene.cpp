#include "Scene.h"
#include "GraphicManager.h"
#include "EnemyDesigner.h"
#include <vector>

///
///@brief Constructor, creates scene based on delivered map
///@param map logical map
///
Scene::Scene(Map map): squareArray(sf::Quads), m_Map(map)
{
	load();
}

///
///@brief Prepares array of verticles according to logical map
///
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

///
///@brief Updates object on the scene
///
///Adds new objects to scene, moves objects, checks collisions and removes inactive objects
///
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

///
///@brief Draws scene to a target
///
///Inherited by sf:Dravable
///@param target render target (typically window)
///@param states render states, such as transform, texture, etc.
///
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
	cashText.setPosition(target.getView().getSize().x - 125, 0);
	target.draw(cashText, states);
}

///
///@brief Gets center of square corresponding to a particular point
///@param p point describing a square
///@returns center of indicated square
///
sf::Vector2f Scene::getSquareOrigin(Point p) const
{
	GraphicManager &cfg = GraphicManager::getInstance();
	const sf::Vertex* square = &squareArray[(p.GetY() * cfg.getWidth() + p.GetX()) * 4];
	sf::Vector2f top_left = square[0].position;
	sf::Vector2f bot_right = square[2].position;
	return sf::Vector2f((bot_right.x + top_left.x) / 2, (bot_right.y + top_left.y) / 2);
}

///
///@brief Gets object of logical map
///@returns map
///
const Map & Scene::getMap() const
{
	return m_Map;
}

///
///@brief Removes outdated moveable objects from scene
///
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

///
///@brief Sets and loads object managing towers
///@param tower pointer to new TowerManager object
///
void Scene::setTowers(TowerManager *tower)
{
	this->tm = tower;
	towers.load(*tm);
}

///
///@brief Gets collection of moveable obiects
///@returns vector of moveable obiects
///
MoveableVector Scene::GetMoveableObjects()
{
	return m_MoveableObjects;
}

///
///@brief Check if there are any enemies or bullets on the scene
///@returns true if wave still lasts, false otherwise
///
bool Scene::EndOfWave()
{
	return m_MoveableObjects.size() == 0;
}

///
///@brief Check if there are enemies at the end of path
///
///All enemies that have achieved end of the path are killed and total damage is computed
///@returns total damage done by the enemies
///
int Scene::EnemyAtEnd()
{
	int retVal=0;
	for (auto enemy : m_MoveableObjects)
	{
		EnemyDesigner* enemyObj;
		if (enemyObj = dynamic_cast<EnemyDesigner*>(enemy))
		{
			if (enemyObj->GetPosition() == m_Map.GetLastPoint())
			{
				retVal += enemyObj->GetDamage();
				enemyObj->setHealth(0);
			}
		}
	}
	return retVal;
}

///
///@brief Destructor
///
Scene::~Scene()
{
}

///
///@brief Adds moveable object to collection
///@param obj pointer to moveable object
///
void Scene::PushObject(IMoveable * obj)
{
	m_MoveableObjects.push_back(obj);
}

