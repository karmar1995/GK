#pragma once
#include "EnemyDesigner.h"
class BulletDesigner : public IMoveable
{
	bool m_verticalMove;
	bool m_MoveEnd;
	sf::Vector2f m_origin;
	sf::Vector2f m_distance;
	sf::Vector2f m_destination;
	sf::VertexArray m_vertex;
	sf::Vector2f m_dimensions;
	sf::Color m_color;
	double m_directionFactorX;
	double m_directionFactorY;
	uint m_damage;
	uint m_speed;
public:
	explicit BulletDesigner(sf::Vector2f startPoint, sf::Vector2f destinationPoint, sf::Vector2f dimensions, uint damage, uint speed);
	virtual uint GetSpeed() override;
	virtual void Move(const Map& m, const Scene& scene) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	virtual bool Collides(IMoveable* other) override;
	virtual void Collision(IMoveable* other) override;
	virtual sf::FloatRect GetRect() override;
	virtual bool Removeable() override;
	~BulletDesigner();
private:
	void step();
	sf::Vector2f updateDistance();
	void UpdateVertex();
};

