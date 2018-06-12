#pragma once
#include "EnemyDesigner.h"



///
///@brief Class representing bullet
///
class BulletDesigner : public IMoveable
{
	bool m_verticalMove;  //logical variable indicating wheter vertical move is needed
	bool m_MoveEnd; //logical indicating whether bullet hit end position
	sf::Vector2f m_origin; // vector representing origin of a bullet
	sf::Vector2f m_distance;  //distance to the end
	sf::Vector2f m_destination; // vector representing coordinates of destination
	sf::VertexArray m_vertex; ///array of bullet's vertex("Corners")
	sf::Vector2f m_dimensions; //size of rectangle in two dimensions
	sf::Color m_color; //color of rectangle
	double m_directionFactorX; //factor used in multiplying by step, for the purpose of object moving-x axis
	double m_directionFactorY; //factor used in multiplying by step, for the purpose of object moving-y axis
	uint m_damage; //damage of bullet
	uint m_speed; //speed of bullet
public:
	explicit BulletDesigner(sf::Vector2f startPoint, sf::Vector2f destinationPoint, sf::Vector2f dimensions, uint damage, uint speed);
	virtual uint GetSpeed() override;
	virtual void Move(const Map& m, const Scene& scene) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	virtual bool Collides(IMoveable* other) override;
	virtual void Collision(IMoveable* other) override;
	virtual sf::FloatRect GetRect() override;
	virtual bool Removeable() override;
	virtual sf::Vector2f GetOrigin() override;
	~BulletDesigner();
private:
	void step();
	sf::Vector2f updateDistance();
	void UpdateVertex();
};

