#include "EnemyDesigner.h"
#include "Scene.h"


EnemyDesigner::EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureOrigin)
{
	m_isMoving = false;
	m_EnemyObject = enemyObject;
	m_origin = origin;
	m_dimensions = dimensions;
	m_color = color;
	m_enemyVertex = sf::VertexArray(sf::Quads, 4);
	/*
	m_enemyVertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y - (dimensions.y / 2)), color);
	m_enemyVertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (dimensions.x / 2), m_origin.y + (dimensions.y / 2)), color);
	m_enemyVertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y + (dimensions.y / 2)), color);
	m_enemyVertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (dimensions.x / 2), m_origin.y - (dimensions.y / 2)), color);
	*/

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
	/*
	sprite.setPosition(m_origin.x, m_origin.y);
	
	m_enemyVertex[SquareCorner::top_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0,0));
	m_enemyVertex[SquareCorner::bot_left] = sf::Vertex(sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//, sf::Vector2f(0, textureDimensions.y));
	m_enemyVertex[SquareCorner::bot_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2)), m_color);//,sf::Vector2f(textureDimensions.x, textureDimensions.y));
	m_enemyVertex[SquareCorner::top_right] = sf::Vertex(sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2)), m_color);// , sf::Vector2f(textureDimensions.x, 0));
	*/
	m_enemyVertex[0].position = sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2));
	m_enemyVertex[1].position = sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y - (m_dimensions.y / 2));
	m_enemyVertex[2].position = sf::Vector2f(m_origin.x + (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2));
	m_enemyVertex[3].position = sf::Vector2f(m_origin.x - (m_dimensions.x / 2), m_origin.y + (m_dimensions.y / 2));




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
}

sf::FloatRect EnemyDesigner::GetRect()
{
	return m_enemyVertex.getBounds();
}
void EnemyDesigner::setHealth(uint health) {
	m_EnemyObject.setHealth(health);
}


sf::Vector2f EnemyDesigner::GetOrigin()
{
	return m_origin;
}


EnemyDesigner::~EnemyDesigner()
{
}


Bird::Bird(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions,std::string textureFile) :EnemyDesigner(EnemyBase(5,5,15), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::White,0);
	tileset.loadFromImage(image);
};

Snake::Snake(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile ) :EnemyDesigner(EnemyBase(10, 10, 11), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::White, 0);
	tileset.loadFromImage(image);
};
Zombie::Zombie(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile) :EnemyDesigner(EnemyBase(50, 20, 7), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};
Vampire::Vampire(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile ) :EnemyDesigner(EnemyBase(65, 10, 5), origin, dimensions, color, textureDimensions) {

	if (!image.loadFromFile(textureFile))
		throw std::runtime_error("Unable to open texture file");
	image.loadFromFile(textureFile);
	image.createMaskFromColor(sf::Color::Black, 0);
	tileset.loadFromImage(image);
};

