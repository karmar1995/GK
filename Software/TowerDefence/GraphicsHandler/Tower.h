#pragma once
class Tower
{
public:
	Tower(int x, int y);
	virtual ~Tower();

	int getX() const;
	int getY() const;
	int getLevel() const;

	static int getPrice();

	double getDamage() const;
	double getAccuracy() const;
	double getReloadSpeed() const;
	double getShootSpeed() const;

	bool upgrade();

	//bool visible(Enemy e);
	//Enemy chooseAim();
	//void fire(Enemy e);

protected:
	int xPos;
	int yPos;
	int level;


	static const int price;
	static const double range;
	static const double damage;
	static const double accuracy;
	static const double reloadSpeed;
	static const double shootSpeed;
	static const double upgradeRatio;
	static const int maxLevel;
};

