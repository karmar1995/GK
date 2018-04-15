#include "Tower.h"
#include "Scene.h"

const int Tower::price = 0;
const double Tower::range = 100;
const uint Tower::damage = 1;
const double Tower::accuracy = 0.8;
const int Tower::reloadSpeed = 1000;
const double Tower::shootSpeed = 5;
const double Tower::upgradeRatio = 1.2;
const int Tower::maxLevel = 3;

Tower::Tower(int x, int y) : xPos(x), yPos(y), level(0), reloadTimer(0)
{
	Pos = Point(x, y);
}

Tower::Tower(const Tower & t) : Tower(t.xPos, t.yPos)
{
	level = t.level;
	reloadTimer = t.reloadTimer;
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

uint Tower::getDamage() const
{
	return damage*pow(upgradeRatio, level);
}

double Tower::getAccuracy() const
{
	return accuracy + (1 - accuracy)*pow(upgradeRatio, level) / pow(upgradeRatio, maxLevel);
}

int Tower::getReloadSpeed() const
{
	return reloadSpeed / pow(upgradeRatio, level);
}

double Tower::getShootSpeed() const
{
	return shootSpeed*pow(upgradeRatio, level);
}

double Tower::getRange() const
{
	return range*pow(upgradeRatio, level);;
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

BulletDesigner* Tower::fire(EnemyDesigner * enemy, const Scene& scene)
{
	if (reloadTimer == 0)
	{
		if (sqrt(pow(enemy->getOrigin().x - scene.getSquareOrigin(Pos).x, 2) + pow(enemy->getOrigin().y - scene.getSquareOrigin(Pos).y, 2)) > getRange())
			return nullptr;
		auto distance = aim(0, enemy->getOrigin() - scene.getSquareOrigin(Pos), enemy->GetPosition(), enemy->GetSpeed(), scene);
		if (sqrt(distance.x*distance.x + distance.y*distance.y) <= getRange())
		{
			reloadTimer = getReloadSpeed();
			return new BulletDesigner(scene.getSquareOrigin(Pos), scene.getSquareOrigin(Pos) + distance, sf::Vector2f(10, 5), getDamage(), getShootSpeed());
		}
	}
	else
		reloadTimer--;
	return nullptr;
}

sf::Vector2f Tower::aim(double time, sf::Vector2f distance, Point &enemyPosition, int enemySpeed, const Scene& scene) const
{
	double a, b, c;
	sf::Vector2f enemyDestination = scene.getSquareOrigin(enemyPosition) - scene.getSquareOrigin(Pos) - distance;
	if (fabs(enemyDestination.x)>fabs(enemyDestination.y))
		enemyDestination.y = 0;
	else
		enemyDestination.x = 0;
	a = enemySpeed*enemySpeed - shootSpeed*shootSpeed;
	c = distance.x*distance.x + distance.y*distance.y - time*time*shootSpeed*shootSpeed;
	if (enemyDestination.x != 0)
	{
		if (distance.x != 0 && enemyDestination.x / distance.x>0)
			b = 2 * (int)enemySpeed * fabs(distance.x);
		else
			b = -2 * (int)enemySpeed * fabs(distance.x);
	}
	else
	{
		if (distance.y != 0 && enemyDestination.y / distance.y>0)
			b = 2 * (int)enemySpeed * fabs(distance.y);
		else
			b = -2 * (int)enemySpeed * fabs(distance.y);
	}
	b -= 2 * time*shootSpeed*shootSpeed;
	double delta = b*b - 4 * a*c;
	delta = sqrt(delta);
	double t1 = (-b + delta) / (2 * a);
	double t2 = (-b - delta) / (2 * a);
	double t = 0;
	if (t1 <= 0 && t2 >= 0)
		t = t2;
	else if (t1 >= 0 && t2 <= 0)
		t = t1;
	else if (t1 >= 0 && t2 >= 0)
		t = (t1 > t2 ? t2 : t1);
	double step = t*enemySpeed;
	if (step > fabs(enemyDestination.x) && step > fabs(enemyDestination.y))
	{
		return aim(fabs(enemyDestination.x / enemySpeed + enemyDestination.y / enemySpeed) + time + 1, distance + enemyDestination,
			scene.getMap().GetPoint(enemyPosition.GetNext().GetX(), enemyPosition.GetNext().GetY()), enemySpeed, scene);
	}
	if (enemyDestination.x != 0)
		distance.x += step;
	else
		distance.y += step;
	return distance;
}
