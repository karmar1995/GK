#include "Tower.h"

const int Tower::price = 0;
const double Tower::range = 25;
const double Tower::damage = 0.1;
const double Tower::accuracy = 0.8;
const double Tower::reloadSpeed = 5;
const double Tower::shootSpeed = 5;
const double Tower::upgradeRatio = 1.2;
const int Tower::maxLevel = 4;

Tower::Tower(int x, int y): xPos(x), yPos(y), level(1)
{
}

Tower::~Tower()
{
}

int Tower::getX() const
{
	return xPos;
}

int Tower::getY() const
{
	return yPos;
}

int Tower::getLevel() const
{
	return level;
}

int Tower::getPrice()
{
	return price;
}

double Tower::getDamage() const
{
	return damage*level*upgradeRatio;
}

double Tower::getAccuracy() const
{
	return accuracy*level*upgradeRatio;
}

double Tower::getReloadSpeed() const
{
	return reloadSpeed*level*upgradeRatio;
}

double Tower::getShootSpeed() const
{
	return shootSpeed*level*upgradeRatio;
}

bool Tower::upgrade()
{
	if (level < maxLevel)
	{
		level++;
		return true;
	}
	return false;
}
