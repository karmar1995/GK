#pragma once
#include "EnemyDesigner.h"
#include <vector>
class Wave
{
public:
	int getWaveId();
	Wave();
	Wave(std::vector<std::tuple <int, EnemyDesigner*>> enemiesVector);
	void setEnemies(std::vector<std::tuple <int, EnemyDesigner*>> enemiesVector);
	void addEnemy(int numberOfEnemies, EnemyDesigner* enemy);
	void clearEnemies();
protected:
	int waveId;
	std::vector<std::tuple <int,EnemyDesigner*>> enemiesVector;
};

