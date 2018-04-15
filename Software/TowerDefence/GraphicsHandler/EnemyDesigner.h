#pragma once
#include "GraphicManager.h"
#include "Utils.hpp"
#include "Map.hpp"
#include "EnemyBase.hpp"



class Scene;

class IMoveable
{
public:
	virtual uint GetSpeed() = 0;
	virtual void Move(const Map& m, const Scene& scene) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	virtual bool Collides(IMoveable* other) = 0;
	virtual void Collision(IMoveable* other) = 0;
	virtual sf::FloatRect GetRect() = 0;
	virtual bool Removeable() = 0;
};
enum SquareCorner {
	top_left, bot_left, bot_right, top_right
};
class EnemyDesigner : public IMoveable
{

	sf::Vector2f m_dimensions;
	sf::Color m_color;
	sf::VertexArray m_enemyVertex;
	sf::Vector2f m_origin;
	sf::Vector2f m_distance;
	sf::Vector2f m_destination;
	EnemyBase m_EnemyObject;
	uint m_CollisionDelay;
	uint m_StepsGone;
	bool m_isMoving;
private:
	void step();
	void MoveToPoint();
	void UpdateVertex();

public:
	EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions);
	sf::VertexArray getEnemyVertex();
	sf::Vector2f getOrigin();
	uint GetSteps();
	virtual uint GetSpeed() override;
	virtual void Move(const Map& m, const Scene& scene) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	virtual bool Collides(IMoveable* other) override;
	virtual void Collision(IMoveable* other) override;
	virtual sf::FloatRect GetRect() override;
	virtual bool Removeable() override;
	void Hit(uint amount);
	Point GetPosition();
	~EnemyDesigner();
};

