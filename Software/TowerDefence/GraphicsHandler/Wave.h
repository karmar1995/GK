#pragma once
#include "EnemyDesigner.h"
#include <vector>
class Wave
{
public:
	int getWaveId();
	void setWaveId(int waveId);
	Wave();
	Wave(std::vector<std::tuple <int, EnemyDesigner*>> enemiesVector,int waveId);
	void setEnemies(std::vector<std::tuple <int, EnemyDesigner*>> enemiesVector);
	void addEnemy(int numberOfEnemies, EnemyDesigner* enemy);
	void clearEnemies();
	std::vector <std::tuple <int, EnemyDesigner*>> getEnemiesVector();

protected:
	int waveId;
	std::vector<std::tuple <int,EnemyDesigner*>> enemiesVector;
};

