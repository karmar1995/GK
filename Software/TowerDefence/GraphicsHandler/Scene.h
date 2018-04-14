#pragma once
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "EnemyDesigner.h"
class Scene : public sf::Drawable, public sf::Transformable
{
	Map m_Map;
	std::vector<IMoveable*> m_MoveableObjects;
public:
	Scene(Map map);
	void load();
	virtual ~Scene();
	void PushObject(IMoveable* obj);
	void DeleteObject(IMoveable* obj);
	sf::Vector2f Scene::getSquareOrigin(Point p) const;
	void Cleanup();
private:
	void UpdateScene() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::VertexArray squareArray;

};

