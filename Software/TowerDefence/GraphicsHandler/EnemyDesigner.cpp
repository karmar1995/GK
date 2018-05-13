#include "EnemyDesigner.h"
#include "Scene.h"

#define COLLISION_DELAY_VALUE 100

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

sf::VertexArray EnemyDesigner::getEnemyVertex()
{
	return m_enemyVertex;
}

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
	m_enemyVertex[0].position = sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2));
	m_enemyVertex[1].position = sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2));
	m_enemyVertex[2].position = sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2));
	m_enemyVertex[3].position = sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2));

}

sf::Vector2f EnemyDesigner::GetOrigin()
{
	return m_origin;
}

uint EnemyDesigner::GetSteps()
{
	return m_StepsGone;
}

uint EnemyDesigner::GetSpeed()
{
	return m_EnemyObject.GetSpeed();
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
	
	target.draw(m_enemyVertex,&tileset);
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

void EnemyDesigner::setHealth(uint health) {
	m_EnemyObject.setHealth(health);
}


bool EnemyDesigner::Removeable()
{
	return m_EnemyObject.GetHealth() <= 0;
}

void EnemyDesigner::Hit(uint amount)
{
	m_EnemyObject.setHealth(m_EnemyObject.GetHealth() - amount);
}

Point EnemyDesigner::GetPosition()
{
	return m_EnemyObject.getPosition();
}

int EnemyDesigner::GetValue()
{
	return m_EnemyObject.GetValue();
}

int EnemyDesigner::GetDamage()
{
	return this->m_EnemyObject.GetDamage();
}

EnemyDesigner::~EnemyDesigner()
{
}


Bird::Bird(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions,std::string textureFile) :EnemyDesigner(EnemyBase(15,5,3), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black,0);
	tileset.loadFromImage(image);
};

Snake::Snake(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile ) :EnemyDesigner(EnemyBase(15, 10, 1), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};
Zombie::Zombie(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile) :EnemyDesigner(EnemyBase(7, 20, 2), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};
Vampire::Vampire(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile ) :EnemyDesigner(EnemyBase(45, 10, 1), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};

