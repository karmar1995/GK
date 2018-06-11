#include "EnemyBase.hpp"


///@brief getter for Enemy's position
///@returns enemy position
Point EnemyBase::getPosition()
{
	return m_Position;
}


///@brief Methods for making step on the map
//It takes next position of the point and set current position to that point
///@param reference to Map
void EnemyBase::Step(const Map& m)
{
	Point tmp = m_Position.GetNext();
	m_Position = m.GetPoint(tmp.GetX(), tmp.GetY());
}

///@brief setter for Enemy's health
//@param health
void EnemyBase::setHealth(int health) 
{
	m_Stats.SetHealth(health);
}


///@brief setter for Enemy's health
//@param health
int EnemyBase::GetHealth()
{
	return m_Stats.GetHealth();
}

///@brief getter for speed
int EnemyBase::GetSpeed()
{
	return m_Stats.GetSpeed();
}

///@brief getter for stats value
int EnemyBase::GetValue()
{
	return m_Stats.GetValue();;
}
///@brief getter for damage
int EnemyBase::GetDamage()
{
	return m_Stats.GetDamage();
}


///@brief constructor with parameter
//this constructor takes point as parameter and set current position to this point
//@param Point 
EnemyBase::EnemyBase(Point p)
{
	m_Position = p;
}

///@brief constructor with parameter
//this constructor takes point as parameter and set current position to this point
//@param Point 
EnemyBase::EnemyBase(uint health, uint damage, uint speed)
{
	m_Stats = Statistics(health, damage, speed);
}


///@brief constructor with parameters
//this constructor takes point, health, damage and speed as parameters
//@param Point 
//@param health 
//@param damage 
//@param speed 
EnemyBase::EnemyBase(Point p, uint health, uint damage, uint speed)
{
	m_Stats = Statistics(health, damage, speed);
	m_Position = p;
}

///@brief constructor
EnemyBase::EnemyBase()
{
}

///@brief destructor
EnemyBase::~EnemyBase()
{
}

///@brief statistics constructor
//
//@param enemy's health
//@param enemy's damage
//@param enemy's speed
Statistics::Statistics(uint health, uint damage, uint speed)
{
	m_iHealth = health;
	m_iDamage = damage;
	m_iSpeed = speed;
	m_iValue = health + speed + damage;
}

///@brief getter for health
int Statistics::GetHealth()
{
	return m_iHealth;
}

///@brief setter for health
//@param enemy's health
void Statistics::SetHealth(uint health)
{
	m_iHealth = health;
}
///@brief getter for damage
int Statistics::GetDamage()
{
	return m_iDamage;
}
///@brief getter for speed
int Statistics::GetSpeed()
{
	return m_iSpeed;
}
///@brief getter for value 
int Statistics::GetValue()
{
	return m_iValue;
}

///@brief destructor
Statistics::~Statistics()
{
}
