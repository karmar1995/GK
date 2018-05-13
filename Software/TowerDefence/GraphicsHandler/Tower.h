#pragma once
#include "BulletDesigner.h"

class Scene;

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
	sf::Clock m_clock;
	Point Pos;
	int xPos;
	int yPos;
	int level;
	int reloadTimer;


	static const int price;
	static const double range;
	static const uint damage;
	static const double accuracy;
	static const int reloadSpeed;
	static const double shootSpeed;
	static const double upgradeRatio;
	static const int maxLevel;
};

