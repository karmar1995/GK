#pragma once
#include "BulletDesigner.h"

class Scene;

///
///@brief Class representing tower in program logic
///
class Tower
{
public:
	Tower(int x, int y);
	Tower(const Tower& t);
	virtual ~Tower();

	int getX() const;
	int getY() const;
	int getLevel() const;

	static int getPrice();
	static int getMaxLevel();
	int upgradePrice();

	uint getDamage() const;
	double getAccuracy() const;
	int getReloadSpeed() const;
	double getShootSpeed() const;
	double getRange() const;

	bool upgrade();

	//Enemy chooseAim();
	BulletDesigner* fire(EnemyDesigner* enemy, const Scene& scene);

protected:
	sf::Vector2f aim(double time, sf::Vector2f distance, Point &enemyPosition, int enemySpeed, const Scene& scene) const;
	sf::Clock m_clock;		///<Clock measuring time from the last shoot
	Point Pos;				///<Position of tower
	int xPos;				///<X position of tower
	int yPos;				///<Y position of tower
	int level;				///<Level of tower


	static const int price;				///<Tower base price
	static const double range;			///<Shoot range for level 0
	static const uint damage;			///<Shoot damage for level 0
	static const double accuracy;		///<Shoot accuracy for level 0
	static const int reloadSpeed;		///<Minimal time between two shots for level 0
	static const double shootSpeed;		///<Speed of bullet for level 0
	static const double upgradeRatio;	///<Ratio of increasing parameters of tower at upgrade
	static const int maxLevel;			///<Maximal level of tower
};

