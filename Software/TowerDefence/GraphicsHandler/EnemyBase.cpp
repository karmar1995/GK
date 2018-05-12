#include "EnemyBase.hpp"



Point EnemyBase::getPosition()
{
	return m_Position;
}

void EnemyBase::Step(const Map& m)
{
	Point tmp = m_Position.GetNext();
	m_Position = m.GetPoint(tmp.GetX(), tmp.GetY());
}

void EnemyBase::setHealth(uint health) 
{
	m_Stats.SetHealth(health);
}

uint EnemyBase::GetHealth()
{
	return m_Stats.GetHealth();
}

uint EnemyBase::GetSpeed()
{
	return m_Stats.GetSpeed();
}

uint EnemyBase::GetValue()
{
	return m_Stats.GetValue();;
}

EnemyBase::EnemyBase(Point p)
{
	m_Position = p;
}

EnemyBase::EnemyBase(uint health, uint damage, uint speed)
{
	m_Stats = Statistics(health, damage, speed);
}

EnemyBase::EnemyBase(Point p, uint health, uint damage, uint speed)
{
	m_Stats = Statistics(health, damage, speed);
	m_Position = p;
}

EnemyBase::EnemyBase()
{
}


EnemyBase::~EnemyBase()
{
}


Statistics::Statistics(uint health, uint damage, uint speed)
{
	m_iHealth = health;
	m_iDamage = damage;
	m_iSpeed = speed;
	m_iValue = health + speed + damage;
}

uint Statistics::GetHealth()
{
	return m_iHealth;
}

void Statistics::SetHealth(uint health)
{
	m_iHealth = health;
}

uint Statistics::GetDamage()
{
	return m_iDamage;
}

uint Statistics::GetSpeed()
{
	return m_iSpeed;
}

uint Statistics::GetValue()
{
	return m_iValue;
}


Statistics::~Statistics()
{
}
