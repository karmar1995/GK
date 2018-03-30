#include "EnemyDesigner.h"
#include "Scene.h"


EnemyDesigner::EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions)
{
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

void EnemyDesigner::step(sf::Vector2f& newOrigin)
{
	float step = 0.01;
	if (std::abs(m_distance.x) > 0)
	{
		if (m_distance.x > 0)
		{
			m_distance.x -= step;
			newOrigin.x += step;
			if (m_distance.x < 0)
				m_distance.x = 0;
		}
		if (m_distance.x < 0)
		{
			m_distance.x += step;
			newOrigin.x -= step;
			if (m_distance.x > 0)
				m_distance.x = 0;
		}
	}
	if (std::abs(m_distance.y)> 0)
	{
		if (m_distance.y > 0)
		{
			m_distance.y -= step;
			newOrigin.y += step;
			if (m_distance.y < 0)
				m_distance.y = 0;
		}
		if (m_distance.y < 0)
		{
			m_distance.y += step;
			newOrigin.y -= step;
			if (m_distance.y > 0)
				m_distance.y = 0;
		}
	}

}

void EnemyDesigner::MoveToPoint()
{
	if(m_isMoving == false)
		m_distance = m_destination - m_origin;
	if(std::abs(m_distance.x)>0 || std::abs(m_distance.y)>0)
	{
		sf::Vector2f newOrigin = m_origin;
		m_isMoving = true;
		step(newOrigin);
		UpdateOrigin(sf::Vector2f(newOrigin));
		m_origin = newOrigin;
		return;
	}
	m_isMoving = false;
}

void EnemyDesigner::UpdateOrigin(sf::Vector2f newOrigin)
{
	m_origin = newOrigin;
	m_enemyVertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0,0));
	m_enemyVertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0, textureDimensions.y));
	m_enemyVertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//,sf::Vector2f(textureDimensions.x, textureDimensions.y));
	m_enemyVertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);// , sf::Vector2f(textureDimensions.x, 0));
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
}

sf::FloatRect EnemyDesigner::GetRect()
{
	return m_enemyVertex.getBounds();
}


EnemyDesigner::~EnemyDesigner()
{
}
