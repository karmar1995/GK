#pragma once
#include "Map.hpp"
#include "Utils.hpp"

class Statistics
{
	uint m_iHealth;
	uint m_iDamage;
	uint m_iSpeed;
public:
	explicit Statistics(uint health=0, uint damage=0, uint speed=0);
	uint GetHealth();
	void SetHealth(uint health);
	uint GetDamage();
	uint GetSpeed();
	~Statistics();
};

enum EnemyTextureType { Empty };

class EnemyBase
{
protected:
	Point m_Position;
	Statistics m_Stats;
	EnemyTextureType m_Texture;
#ifdef _DEBUG
public:
#endif
	Point getPosition();
	void Step(const Map& m);
	EnemyBase();
	EnemyBase(Point p);
	~EnemyBase();
};