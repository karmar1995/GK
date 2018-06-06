#pragma once
#include <SFML/Graphics.hpp>
#include "TowerManager.h"

///
///@brief Class managing drawing of towers
///
class TowerGraphic : public sf::Drawable, public sf::Transformable
{
public:
	TowerGraphic();
	void load(const TowerManager& tm);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual ~TowerGraphic();
private:
	
	sf::VertexArray towerArray; ///<Array of verticles used to speed-up rendering process
};

