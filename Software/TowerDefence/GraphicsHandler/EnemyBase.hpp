#pragma once
#include "Map.hpp"
#include "Utils.hpp"

class Statistics
{
	uint m_iHealth;
	uint m_iDamage;
	uint m_iSpeed;
	uint m_iValue;
public:
	explicit Statistics(uint health = 0, uint damage = 0, uint speed = 0);
	uint GetHealth();
	void SetHealth(uint health);
	uint GetDamage();
	uint GetSpeed();
	uint GetValue();
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
	void setHealth(uint health);
	uint GetHealth();
	uint GetSpeed();
	uint GetValue();

	EnemyBase();
	EnemyBase(Point p);
	EnemyBase(uint health, uint damage , uint speed );
	EnemyBase(Point p, uint health, uint damage, uint speed);
	~EnemyBase();
};