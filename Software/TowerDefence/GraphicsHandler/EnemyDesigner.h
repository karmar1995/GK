#pragma once
#include "GraphicManager.h"
#include "Utils.hpp"
#include "Map.hpp"
#include "EnemyBase.hpp"



class Scene;

///
///@brief Interface representing enemy's possible
///
class IMoveable
{
public:
	virtual uint GetSpeed() = 0;
	virtual void Move(const Map& m, const Scene& scene) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) = 0;
	virtual bool Collides(IMoveable* other) = 0;
	virtual void Collision(IMoveable* other) = 0;
	virtual sf::Vector2f GetOrigin() = 0;
	virtual sf::FloatRect GetRect() = 0;
	virtual bool Removeable() = 0;
};
enum SquareCorner {
	top_left, bot_left, bot_right, top_right
};

///
///@brief Class representing physical monster
///
class EnemyDesigner : public IMoveable
{
protected:
	sf::Vector2f m_dimensions;  //size of rectangle in two dimensions
	sf::Color m_color;  //color of background
	sf::VertexArray m_enemyVertex; //array of enemy's vertex("Corners")
	sf::Vector2f m_origin; //2d structure representing origin(central point)
	sf::Vector2f m_distance; //2d structure representing origin(central point)
	sf::Vector2f m_destination; //2d structure representing origin(central point)
	EnemyBase m_EnemyObject; //logical part of enemy
	uint m_CollisionDelay; 
	uint m_StepsGone;
	bool m_isMoving; //logical describing wheter enemy is moving
	sf::Texture tileset; //enemy's texture
	sf::Image image;
	std::string textureFile; //texture file from which the texture is loaded

	void step();
	void MoveToPoint();
	void UpdateVertex();

public:
	EnemyDesigner(EnemyBase enemyObject, sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureOrigin= sf::Vector2f(0,0));
	sf::VertexArray getEnemyVertex();
//	void MoveToPoint();
	void UpdateOrigin(sf::Vector2f newOrigin);
	uint GetSteps();
	virtual sf::Vector2f GetOrigin() override;
	virtual uint GetSpeed() override;
	virtual void Move(const Map& m, const Scene& scene) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) override;
	virtual bool Collides(IMoveable* other) override;
	virtual void Collision(IMoveable* other) override;
	virtual sf::FloatRect GetRect() override;
	virtual bool Removeable() override;
	void Hit(uint amount);
	Point GetPosition();
	int GetValue();
	int GetDamage();
	virtual void setHealth(uint health);
	std::string transparencyColor;
	~EnemyDesigner();
};


///
///@brief Class representing bird
///
class Bird :public EnemyDesigner {

public:
	Bird(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions,std::string textureFile="setOfMonsters.png") ;
};


///
///@brief Class representing zombie
///
class Zombie :public EnemyDesigner {

public:
	Zombie(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string = "zombie.png");
};

///
///@brief Class representing snake
///
class Snake :public EnemyDesigner {

public:
	Snake( sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile = "setOfMonsters.png");
};

///
///@brief Class representing vampire
///
class Vampire :public EnemyDesigner {

public:
	Vampire(sf::Vector2f origin, sf::Vector2f dimensions, sf::Color color, sf::Vector2f textureDimensions, std::string textureFile="vampire.png");
};
