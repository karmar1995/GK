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

EnemyBase::EnemyBase()
{
}

EnemyBase::EnemyBase(Point p)
{
	m_Position = p;
}


EnemyBase::~EnemyBase()
{
}


Statistics::Statistics(uint health, uint damage, uint speed)
{
	m_iHealth = health;
	m_iDamage = damage;
	m_iSpeed = speed;
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

Statistics::~Statistics()
{
}
