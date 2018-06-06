#include "Tower.h"
#include "Scene.h"

const int Tower::price = 80;
const double Tower::range = 100;
const uint Tower::damage = 1;
const double Tower::accuracy = 0.8;
const int Tower::reloadSpeed = 10000;
const double Tower::shootSpeed = 5;
const double Tower::upgradeRatio = 1.2;
const int Tower::maxLevel = 3;

///
///@brief Constructor, creates tower in specified location
///@param x x coordinate of tower in logic coordinates
///@param y y coordinate of tower in logic coordinates
///
Tower::Tower(int x, int y) : xPos(x), yPos(y), level(0)
{
	Pos = Point(x, y);
}

///
///@brief Copy constructor
///@param t reference of tower object
///
Tower::Tower(const Tower & t) : Tower(t.xPos, t.yPos)
{
	level = t.level;
}

///
///@brief Destructor
///
Tower::~Tower()
{
}

///
///@brief Gets x position of tower in squares
///@returns x coordinate of tower
///
int Tower::getX() const
{
	return xPos;
}

///
///@brief Gets y position of tower in squares
///@returns y coordinate of tower
///
int Tower::getY() const
{
	return yPos;
}

///
///@brief Gets level of tower
///@returns level
///
int Tower::getLevel() const
{
	return level;
}

///
///@brief Gets price of tower
///@returns price
///
int Tower::getPrice()
{
	return price;
}

///
///@brief Gets maximal possible level of towers
///@returns maximum tower level
///
int Tower::getMaxLevel()
{
	return maxLevel;
}

///
///@brief Gets costs of upgrading tower to higher level
///@returns price
///
int Tower::upgradePrice()
{
	return (level+1)*price*(upgradeRatio/2.0);
}

///
///@brief Gets damage value of bullets from the tower
///@returns damage value
///
uint Tower::getDamage() const
{
	return damage*pow(upgradeRatio, level);
}

///
///@brief Gets accuracy of shots
///@returns accuracy value
///
double Tower::getAccuracy() const
{
	return accuracy + (1 - accuracy)*pow(upgradeRatio, level) / pow(upgradeRatio, maxLevel);
}

///
///@brief Gets time of reloading
///@returns time of reloading
///
int Tower::getReloadSpeed() const
{
	return reloadSpeed / pow(upgradeRatio, level);
}

///
///@brief Gets speed of bullet
///@returns bullet speed
///
double Tower::getShootSpeed() const
{
	return shootSpeed*pow(upgradeRatio, level);
}

///
///@brief Gets range of shoots
///@returns range
///
double Tower::getRange() const
{
	return range*pow(upgradeRatio, level);;
}

///
///@brief Upgrades tower to higher level
///
///It results in better range, damage and speed \n
///Upgrade is impossible if tower level is equal to maximal level
///@returns true if upgrade succeed, false otherwise
///
bool Tower::upgrade()
{
	if (level < maxLevel)
	{
		level++;
		return true;
	}
	return false;
}

///
///@brief Shoots to indicated enemy if possible
///
///Method checks if shoot can be done, i.e. checks time interval from last shoot and compares range with distance
///If shoot is possible, bullet object is created
///@param enemy pointer to enemy object
///@param scene reference to current scene
///@returns pointer to new bullet object
///@returns nullptr if shoot cannot be done
///
BulletDesigner* Tower::fire(EnemyDesigner * enemy, const Scene& scene)
{
	if (enemy != nullptr)
	{
		if(m_clock.getElapsedTime().asSeconds() >= 0.55f)
		{
			if (sqrt(pow(enemy->GetOrigin().x - scene.getSquareOrigin(Pos).x, 2) + pow(enemy->GetOrigin().y - scene.getSquareOrigin(Pos).y, 2)) > getRange())
				return nullptr;
			auto distance = aim(0, enemy->GetOrigin() - scene.getSquareOrigin(Pos), enemy->GetPosition(), enemy->GetSpeed(), scene);
			if (sqrt(distance.x*distance.x + distance.y*distance.y) <= getRange())
			{
				m_clock.restart();
				return new BulletDesigner(scene.getSquareOrigin(Pos), scene.getSquareOrigin(Pos) + distance, sf::Vector2f(10, 5), getDamage(), getShootSpeed());
			}
		}
	}
	return nullptr;
}

///
///@brief Aims to enemy object
///
///Calculates prediction of enemy movement and computes intersection point of bullet trajectory and enemy track \n
///Method is invoked recursively to predict movement for path with turns
///@param time time since shoot for actual prediction
///@param distance distance between tower and enemy for actual prediction
///@param enemyPosition enemy position for actual prediction
///@param enemySpeed speed of enemy
///@param scene reference to current scene
///@returns motion vector of shoot
///
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
