#pragma once
#include "Map.hpp"
#include "Utils.hpp"
///
///@brief Class representing monster's statistics
///
class Statistics
{
	int m_iHealth;  //monster's current health
	int m_iDamage;  //monster's damage
	int m_iSpeed;  //monster's speed
	int m_iValue;  //monster's value
public:
	explicit Statistics(uint health = 0, uint damage = 0, uint speed = 0);
	int GetHealth();
	void SetHealth(uint health);
	int GetDamage();
	int GetSpeed();
	int GetValue();
	~Statistics();
};


///
///@brief Class representing logical part of enemy
///
class EnemyBase
{
protected:
	Point m_Position;  //current position
	Statistics m_Stats; //current statisticts

public:

	Point getPosition();
	void Step(const Map& m);
	void setHealth(int health);
	int GetHealth();
	int GetSpeed();
	int GetValue();
	int GetDamage();
	EnemyBase();
	EnemyBase(Point p);
	EnemyBase(uint health, uint damage , uint speed );
	EnemyBase(Point p, uint health, uint damage, uint speed);
	~EnemyBase();
};