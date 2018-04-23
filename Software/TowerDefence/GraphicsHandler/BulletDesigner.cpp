#include "BulletDesigner.h"


BulletDesigner::BulletDesigner(sf::Vector2f startPoint, sf::Vector2f destinationPoint, sf::Vector2f dimensions, uint damage, uint speed)
{
	m_damage = damage;
	m_speed = speed;
	m_MoveEnd = false;
	m_color = sf::Color(255, 255, 0);
	m_origin = startPoint;
	m_destination = destinationPoint;
	m_vertex = sf::VertexArray(sf::Quads, 4);
	m_dimensions = dimensions;
	m_vertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y - (dimensions.y / 2)), m_color);
	m_vertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y + (dimensions.y / 2)), m_color);
	m_vertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y + (dimensions.y / 2)), m_color);
	m_vertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y - (dimensions.y / 2)), m_color);
	m_verticalMove = false;
	if (int(destinationPoint.x) != int(startPoint.x)) {
		double d = sqrt((destinationPoint.y - startPoint.y)*(destinationPoint.y - startPoint.y) +
			(destinationPoint.x - startPoint.x) * (destinationPoint.x - startPoint.x));
		m_directionFactorY = (destinationPoint.y - startPoint.y) / d;
		m_directionFactorX = (destinationPoint.x - startPoint.x) / d;
	}
	else
		m_verticalMove = true;
	updateDistance();
}

uint BulletDesigner::GetSpeed()
{
	return m_speed;
}

void BulletDesigner::Move(const Map & m, const Scene & scene)
{
	step();
	UpdateVertex();
}

void BulletDesigner::draw(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(m_vertex);
}

bool BulletDesigner::Collides(IMoveable * other)
{
	return this->GetRect().intersects(other->GetRect());
}

void BulletDesigner::Collision(IMoveable * other)
{
	EnemyDesigner* enemy = dynamic_cast<EnemyDesigner*>(other);
	if (enemy)
	{
		m_MoveEnd = true;
		enemy->Hit(m_damage);
	}
}

sf::FloatRect BulletDesigner::GetRect()
{
	return m_vertex.getBounds();
}

bool BulletDesigner::Removeable()
{
	return m_MoveEnd;
}

sf::Vector2f BulletDesigner::GetOrigin()
{
	return m_origin;
}

BulletDesigner::~BulletDesigner()
{
}

void BulletDesigner::step()
{
	float step = 0.01*m_speed;
	if (m_verticalMove)
	{
		if (std::abs(m_distance.y) > 0)
		{
			if (m_distance.y > 0)
			{
				m_origin.y += step;
				m_distance.y -= step;
				if (m_distance.y <= 0)
				{
					m_distance.y = 0;
					m_MoveEnd = true;
				}
			}
			else
			{
				m_origin.y -= step;
				m_distance.y += step;
				if (m_distance.y >= 0)
				{
					m_distance.y = 0;
					m_MoveEnd = true;
				}
			}
		}
	}
	else if (std::abs(m_distance.x) > 0)
	{
		m_origin.x += (m_directionFactorX * step);
		m_origin.y += (m_directionFactorY * step);
		m_distance.x -= (m_directionFactorX * step);
		if (abs(m_distance.x) <= abs(m_directionFactorX * step))
		{
			m_distance.x = 0;
			m_MoveEnd = true;
		}
	}
}

sf::Vector2f BulletDesigner::updateDistance()
{
	return m_distance = m_destination - m_origin;
}

void BulletDesigner::UpdateVertex()
{
	m_vertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0,0));
	m_vertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0, textureDimensions.y));
	m_vertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//,sf::Vector2f(textureDimensions.x, textureDimensions.y));
	m_vertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);// , sf::Vector2f(textureDimensions.x, 0));
}
