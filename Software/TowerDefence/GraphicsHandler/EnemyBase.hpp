#pragma once
#include "Map.hpp"
#include "Utils.hpp"

class Statistics
{
	int m_iHealth;
	int m_iDamage;
	int m_iSpeed;
	int m_iValue;
public:
	explicit Statistics(uint health = 0, uint damage = 0, uint speed = 0);
	int GetHealth();
	void SetHealth(uint health);
	int GetDamage();
	int GetSpeed();
	int GetValue();
	~Statistics();
};


class EnemyBase
{
protected:
	Point m_Position;
	Statistics m_Stats;

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