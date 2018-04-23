#pragma once
#include <SFML/Graphics.hpp>
#include "TowerManager.h"

class TowerGraphic : public sf::Drawable, public sf::Transformable
{
public:
	TowerGraphic();
	void load(const TowerManager& tm);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual ~TowerGraphic();
private:
	
	sf::VertexArray towerArray;
};

