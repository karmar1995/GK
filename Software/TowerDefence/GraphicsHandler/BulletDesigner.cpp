#include "BulletDesigner.h"

///
///@brief constructor 
///@param point from which bullet start
///@param destinating point where bullet hits
///@param dimensions of background rectangle
///@param bullet's damage
///@param bullet's speed
///
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

///
///@brief getter for bullet's speed 
///@returns bullet's speed
///
uint BulletDesigner::GetSpeed()
{
	return m_speed;
}
///
///@brief Method for moving bullet on the map
///@param reference to Map class
///@param reference to Scene class
///
void BulletDesigner::Move(const Map & m, const Scene & scene)
{
	step();
	UpdateVertex();
}

///
///@brief Method for drawing bullet (basing on current vertex array)
///@param reference to RenderTarget class
///@param reference to RenderStates class
///
void BulletDesigner::draw(sf::RenderTarget & target, sf::RenderStates states)
{
	target.draw(m_vertex);
}

///
///@brief Method for detecting collision with another object
///@param reference to IMoveable class,representing other object
///@returns logical indicating whether collision happend
///
bool BulletDesigner::Collides(IMoveable * other)
{
	return this->GetRect().intersects(other->GetRect());
}

///
///@brief Method for performing collision with another object
///@param reference to IMoveable class,representing other object
///
void BulletDesigner::Collision(IMoveable * other)
{
	EnemyDesigner* enemy = dynamic_cast<EnemyDesigner*>(other);
	if (enemy)
	{
		m_MoveEnd = true;
		enemy->Hit(m_damage);
	}
}

///
///@brief getter for bullet's vertex array bounds
///@returns vertex array boundaries
///
sf::FloatRect BulletDesigner::GetRect()
{
	return m_vertex.getBounds();
}
///
///@brief Method returning m_MoveEnd value
//Methods returns m_moveEnd, needed to detect whether bullet reached final position so it could be removed
///@returns boolean indicating whether end was reached
///
bool BulletDesigner::Removeable()
{
	return m_MoveEnd;
}
///
///@brief getter for bullet's origin point
///@returns origin point
///
sf::Vector2f BulletDesigner::GetOrigin()
{
	return m_origin;
}
///
///@brief destructor
///
BulletDesigner::~BulletDesigner()
{
}
///
///@brief Method used for performing move of bullet
// method checks whether m_verticalMove is true, if so-it checks whether the distance in y
//direction is greater than 0, so it can increase value of y and decrease distance left
//analogous for x direction
///
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

///
///@brief Method used for updating distance
/// method calculates distance between destination and origin
///@returns updated distance 
sf::Vector2f BulletDesigner::updateDistance()
{
	return m_distance = m_destination - m_origin;
}

///
///@brief Method used for updating vertex array
///method calculates rectangle's corners basing on current origin and dimensions
///
void BulletDesigner::UpdateVertex()
{
	m_vertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0,0));
	m_vertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0, textureDimensions.y));
	m_vertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//,sf::Vector2f(textureDimensions.x, textureDimensions.y));
	m_vertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);// , sf::Vector2f(textureDimensions.x, 0));
}
