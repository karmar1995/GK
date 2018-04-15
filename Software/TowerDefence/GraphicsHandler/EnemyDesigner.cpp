#include "EnemyDesigner.h"
#include "Scene.h"

#define COLLISION_DELAY_VALUE 100

EnemyDesigner::EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions)
{
	m_StepsGone = 0;
	m_CollisionDelay = 0;
	m_isMoving = false;
	m_EnemyObject = enemyObject;
	m_origin = origin;
	m_dimensions = dimensions;
	m_color = color;
	m_enemyVertex = sf::VertexArray(sf::Quads, 4);
	m_enemyVertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y - (dimensions.y / 2)), color);
	m_enemyVertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y + (dimensions.y / 2)), color);
	m_enemyVertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y + (dimensions.y / 2)), color);
	m_enemyVertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y - (dimensions.y / 2)), color);
}

sf::VertexArray EnemyDesigner::getEnemyVertex()
{
	return m_enemyVertex;
}

void EnemyDesigner::step()
{
	float step = 0.01;
	if (m_CollisionDelay == 0)
	{
		step *= m_EnemyObject.getStatistics().GetSpeed();
	}
	else
	{
		step = 0;
		m_CollisionDelay--;
	}
	if (std::abs(m_distance.x) > 0)
	{
		if (m_distance.x > 0)
		{
			m_distance.x -= step;
			m_origin.x += step;
			if (m_distance.x < 0)
				m_distance.x = 0;
		}
		if (m_distance.x < 0)
		{
			m_distance.x += step;
			m_origin.x -= step;
			if (m_distance.x > 0)
				m_distance.x = 0;
		}
	}
	if (std::abs(m_distance.y)> 0)
	{
		if (m_distance.y > 0)
		{
			m_distance.y -= step;
			m_origin.y += step;
			if (m_distance.y < 0)
				m_distance.y = 0;
		}
		if (m_distance.y < 0)
		{
			m_distance.y += step;
			m_origin.y -= step;
			if (m_distance.y > 0)
				m_distance.y = 0;
		}
	}
	m_StepsGone++;
	UpdateVertex();
}

void EnemyDesigner::MoveToPoint()
{
	if (m_isMoving == false)
		m_distance = m_destination - m_origin;
	if (std::abs(m_distance.x)>0 || std::abs(m_distance.y)>0)
	{
		m_isMoving = true;
		step();
		return;
	}
	m_isMoving = false;
}

void EnemyDesigner::UpdateVertex()
{
	m_enemyVertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0,0));
	m_enemyVertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0, textureDimensions.y));
	m_enemyVertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//,sf::Vector2f(textureDimensions.x, textureDimensions.y));
	m_enemyVertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);// , sf::Vector2f(textureDimensions.x, 0));
}

sf::Vector2f EnemyDesigner::getOrigin()
{
	return m_origin;
}

uint EnemyDesigner::GetSteps()
{
	return m_StepsGone;
}

uint EnemyDesigner::GetSpeed()
{
	return m_EnemyObject.getStatistics().GetSpeed();
}

void EnemyDesigner::Move(const Map& m, const Scene& scene)
{
	if (!m_isMoving)
	{
		m_EnemyObject.Step(m);
		m_destination = scene.getSquareOrigin(m_EnemyObject.getPosition());
	}
	MoveToPoint();
}

void EnemyDesigner::draw(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(m_enemyVertex);
}

bool EnemyDesigner::Collides(IMoveable * other)
{
	return this->GetRect().intersects(other->GetRect());
}

void EnemyDesigner::Collision(IMoveable * other)
{
	EnemyDesigner* otherEnemy = dynamic_cast<EnemyDesigner*>(other);
	if (otherEnemy)
	{
		if (this->GetSteps() < otherEnemy->GetSteps())
			m_CollisionDelay = COLLISION_DELAY_VALUE;
	}
}

sf::FloatRect EnemyDesigner::GetRect()
{
	return m_enemyVertex.getBounds();
}

bool EnemyDesigner::Removeable()
{
	return m_EnemyObject.getStatistics().GetHealth() == 0;
}

void EnemyDesigner::Hit(uint amount)
{
	m_EnemyObject.getStatistics().SetHealth(m_EnemyObject.getStatistics().GetHealth() - amount);
}

Point EnemyDesigner::GetPosition()
{
	return m_EnemyObject.getPosition();
}


EnemyDesigner::~EnemyDesigner()
{
}
