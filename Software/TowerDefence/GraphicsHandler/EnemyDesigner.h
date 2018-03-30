#pragma once
#include "GraphicManager.h"
#include "Utils.hpp"
#include "Map.hpp"
#include "EnemyBase.hpp"



class Scene;

class IMoveable
{
public:
	virtual void Move(const Map& m, const Scene& scene) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	virtual bool Collides(IMoveable* other) = 0;
	virtual void Collision(IMoveable* other) = 0;
	virtual sf::FloatRect GetRect() = 0;
};

class EnemyDesigner: public IMoveable
{
	enum SquareCorner {
		top_left, bot_left, bot_right, top_right
	};
	sf::Vector2f m_dimensions;
	sf::Color m_color;
	sf::VertexArray m_enemyVertex;
	sf::Vector2f m_origin;
	sf::Vector2f m_distance;
	sf::Vector2f m_destination;
	EnemyBase m_EnemyObject;
	bool m_isMoving;
private:
	void step(sf::Vector2f& newOrigin);
public:
	EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions);
	sf::VertexArray getEnemyVertex();
	void MoveToPoint();
	void UpdateOrigin(sf::Vector2f newOrigin);
	virtual void Move(const Map& m, const Scene& scene) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	virtual bool Collides(IMoveable* other) override;
	virtual void Collision(IMoveable* other) override;
	virtual sf::FloatRect GetRect() override;
	~EnemyDesigner();
};

