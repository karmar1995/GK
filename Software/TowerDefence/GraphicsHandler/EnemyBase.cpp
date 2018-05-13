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

void EnemyBase::setHealth(int health) 
{
	m_Stats.SetHealth(health);
}

int EnemyBase::GetHealth()
{
	return m_Stats.GetHealth();
}

int EnemyBase::GetSpeed()
{
	return m_Stats.GetSpeed();
}

int EnemyBase::GetValue()
{
	return m_Stats.GetValue();;
}

int EnemyBase::GetDamage()
{
	return m_Stats.GetDamage();
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

int Statistics::GetHealth()
{
	return m_iHealth;
}

void Statistics::SetHealth(uint health)
{
	m_iHealth = health;
}

int Statistics::GetDamage()
{
	return m_iDamage;
}

int Statistics::GetSpeed()
{
	return m_iSpeed;
}

int Statistics::GetValue()
{
	return m_iValue;
}


Statistics::~Statistics()
{
}
