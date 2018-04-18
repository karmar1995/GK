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
	virtual sf::Vector2f GetOrigin() = 0;
	virtual sf::FloatRect GetRect() = 0;
};

class EnemyDesigner: public IMoveable
{
protected:
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
	sf::Texture tileset;
	sf::Image image;
	std::string textureFile;

private:
	void step(sf::Vector2f& newOrigin);
public:
	EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureOrigin= sf::Vector2f(0,0));
	sf::VertexArray getEnemyVertex();
	void MoveToPoint();
	void UpdateOrigin(sf::Vector2f newOrigin);
	virtual void Move(const Map& m, const Scene& scene) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	virtual bool Collides(IMoveable* other) override;
	virtual void Collision(IMoveable* other) override;
	virtual sf::FloatRect GetRect() override;
	virtual sf::Vector2f GetOrigin() override;
	virtual void setHealth(uint health);
	std::string transparencyColor;
	~EnemyDesigner();
};

class Bird :public EnemyDesigner {

public:
	Bird(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions,std::string textureFile="setOfMonsters.png") ;
};

class Zombie :public EnemyDesigner {

public:
	Zombie(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string = "zombie.png");
};

class Snake :public EnemyDesigner {

public:
	Snake( sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile = "setOfMonsters.png");
};

class Vampire :public EnemyDesigner {

public:
	Vampire(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile="vampire.png");
};
