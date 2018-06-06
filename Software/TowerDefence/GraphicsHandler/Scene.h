#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "EnemyDesigner.h"
#include "TowerManager.h"
#include "TowerGraphic.h"

typedef std::vector<IMoveable*> MoveableVector;
typedef MoveableVector::iterator MoveableIterator;

///
///@brief Class representing game scene
///
///Contains all graphical elements of game, such as graphical representation of map 
///and collections of towers, enemies, etc. \n
///Object of this type is the main rendered object in game
///
class Scene : public sf::Drawable, public sf::Transformable
{
	Map m_Map;			///<Logic map
	std::vector<IMoveable*> m_MoveableObjects; ///<Collection of moveable objects (enemies and bullets)
	TowerManager * tm;			///<Pointer to object managing towers on scene
	TowerGraphic towers;		///<Object managing drawing and displaying towers

public:
	Scene(Map map);
	void load();
	virtual ~Scene();
	void PushObject(IMoveable* obj);
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
	sf::VertexArray squareArray;		///<Array of verticles used to speed-up rendering process

};

