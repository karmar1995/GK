#include "EnemyDesigner.h"
#include "Scene.h"

#define COLLISION_DELAY_VALUE 100


///@brief constructor 
///
///@param logical enemy object
///@param origin point 
///@param dimensions of background rectangle
///@param backgroud color
///@param origin point of texture
///
EnemyDesigner::EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureOrigin)
{
	m_StepsGone = 0;
	m_CollisionDelay = 0;
	m_isMoving = false;
	m_EnemyObject = enemyObject;
	m_origin = origin;
	m_dimensions = dimensions;
	m_color = color;
	m_enemyVertex = sf::VertexArray(sf::Quads, 4);

	m_enemyVertex[0].position = sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y - (dimensions.y / 2));
	m_enemyVertex[1].position = sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y - (dimensions.y / 2));
	m_enemyVertex[2].position = sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y + (dimensions.y / 2));
	m_enemyVertex[3].position = sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y + (dimensions.y / 2));

	m_enemyVertex[0].texCoords = sf::Vector2f(textureOrigin.x, textureOrigin.y);
	m_enemyVertex[1].texCoords = sf::Vector2f(textureOrigin.x+ dimensions.x, textureOrigin.y);
	m_enemyVertex[2].texCoords = sf::Vector2f(textureOrigin.x + dimensions.x, textureOrigin.y+ dimensions.y);
	m_enemyVertex[3].texCoords = sf::Vector2f(textureOrigin.x, textureOrigin.y + dimensions.y);

}

///
///@brief getter for enemy vertex 
///@returns  array of vertex describing enemy's background
///
sf::VertexArray EnemyDesigner::getEnemyVertex()
{
	return m_enemyVertex;
}

///
///@brief Method used for performing step of enemy
///it tests whether enemy hits something in x and y axis
///
void EnemyDesigner::step()
{
	float step = 0.01;
	if (m_CollisionDelay == 0)
	{
		step *= m_EnemyObject.GetSpeed();
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

///
///@brief Method used for moving towards point
///it performs move when distance in x and y directions are greater than 0
///
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

///
///@brief Method used for updating vertex
///method calculates rectangle's corners basing on current origin and dimensions
///
void EnemyDesigner::UpdateVertex()
{
	m_enemyVertex[0].position = sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2));
	m_enemyVertex[1].position = sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2));
	m_enemyVertex[2].position = sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2));
	m_enemyVertex[3].position = sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2));

}
///
///@brief getter for origin point
///@returns origin
///
sf::Vector2f EnemyDesigner::GetOrigin()
{
	return m_origin;
}
///
///@brief getter for steps
///@returns steps performed
///
uint EnemyDesigner::GetSteps()
{
	return m_StepsGone;
}
///
///@brief getter for speed
///@returns speed
///
uint EnemyDesigner::GetSpeed()
{
	return m_EnemyObject.GetSpeed();
}
///
///@brief Method used for moving object on the map
///If object isn't moving it gets the destination point from scene
///@param reference to map
///@param reference to scene
///
void EnemyDesigner::Move(const Map& m, const Scene& scene)
{
	if (!m_isMoving)
	{
		m_EnemyObject.Step(m);
		m_destination = scene.getSquareOrigin(m_EnemyObject.getPosition());
	}
	MoveToPoint();
}
///
///@brief Method used for drawing object basing on vertex array and tileset
///@param reference to RenderTarget
///@param reference to RenderStates
///
void EnemyDesigner::draw(sf::RenderTarget & target, sf::RenderStates states)
{
	
	target.draw(m_enemyVertex,&tileset);
}
///
//@brief Method used for collision detection
///@param pointer to object representing IMoveable interface
///@returns logical indicating whether collision has happend
///
bool EnemyDesigner::Collides(IMoveable * other)
{
	return this->GetRect().intersects(other->GetRect());
}

///
///@brief Method used for collision detection
///method sets collision delay according to defined COLLISION_DELAY_VALUE
///@param pointer to object representing IMoveable interface
///
void EnemyDesigner::Collision(IMoveable * other)

{
	EnemyDesigner* otherEnemy = dynamic_cast<EnemyDesigner*>(other);
	if (otherEnemy)
	{
		if (this->GetSteps() < otherEnemy->GetSteps())
			m_CollisionDelay = COLLISION_DELAY_VALUE;
	}
}


///
///@brief Getter  for vertex points
///@returns vertex array
///
sf::FloatRect EnemyDesigner::GetRect()
{
	return m_enemyVertex.getBounds();
}

///
///@brief Setter for enemy's health
///@param health value
///
void EnemyDesigner::setHealth(uint health) {
	m_EnemyObject.setHealth(health);
}
///
///@brief Method checks whether health is lower than 0 so it can be removed
///@returns logical indicating whether object can be removed
///
bool EnemyDesigner::Removeable()
{
	return m_EnemyObject.GetHealth() <= 0;
}
///
///@brief Method used for changing health when being hit
///@param hit strength 
///
void EnemyDesigner::Hit(uint amount)
{
	m_EnemyObject.setHealth(m_EnemyObject.GetHealth() - amount);
}
///
///@brief getter for position
///@returns current position
///
Point EnemyDesigner::GetPosition()
{
	return m_EnemyObject.getPosition();
}
///
///@brief getter for value of the enemy
///@returns  value of the enemy value
///
int EnemyDesigner::GetValue()
{
	return m_EnemyObject.GetValue();
}
///
///@brief getter for enemy's damage
///@returns enemy's damage
///
int EnemyDesigner::GetDamage()
{
	return this->m_EnemyObject.GetDamage();
}
///
///@brief  destructor
///
EnemyDesigner::~EnemyDesigner()
{
}
///
///@brief  constructor for bird class
///@param origin point
///@param dimensions
///@param color
///@param texture dimensions
///@param file containing texture
///
Bird::Bird(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions,std::string textureFile) :EnemyDesigner(EnemyBase(15,5,3), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black,0);
	tileset.loadFromImage(image);
};

///
///@brief  constructor for snake class
///@param origin point
///@param dimensions
///@param color
///@param texture dimensions
///@param file containing texture
///
Snake::Snake(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile ) :EnemyDesigner(EnemyBase(15, 10, 1), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};

///
///@brief  constructor for zombie class
///@param origin point
///@param dimensions
///@param color
///@param texture dimensions
///@param file containing texture
///
Zombie::Zombie(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile) :EnemyDesigner(EnemyBase(7, 20, 2), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};

///
///@brief  constructor for vampire class
///@param origin point
///@param dimensions
///@param color
///@param texture dimensions
///@param file containing texture
///
Vampire::Vampire(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile ) :EnemyDesigner(EnemyBase(45, 10, 1), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};

