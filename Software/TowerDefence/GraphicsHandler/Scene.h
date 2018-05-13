#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "EnemyDesigner.h"
#include "TowerManager.h"
#include "TowerGraphic.h"

typedef std::vector<IMoveable*> MoveableVector;
typedef MoveableVector::iterator MoveableIterator;

class Scene : public sf::Drawable, public sf::Transformable
{
	Map m_Map;
	std::vector<IMoveable*> m_MoveableObjects;
	TowerManager * tm;
	TowerGraphic towers;

public:
	Scene(Map map);
	void load();
	virtual ~Scene();
	void PushObject(IMoveable* obj);
	void DeleteObject(IMoveable* obj);
	sf::Vector2f Scene::getSquareOrigin(Point p) const;
	const Map & getMap() const;
	void Cleanup();
	void UpdateScene();
	void setTowers(TowerManager *tower);
	MoveableVector GetMoveableObjects();
	bool EndOfWave();
	int EnemyAtEnd();
private:
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray squareArray;

};

