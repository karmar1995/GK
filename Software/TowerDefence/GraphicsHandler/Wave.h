#pragma once
#include "EnemyDesigner.h"
#include <vector>
class Wave
{
public:
	int getWaveId();
	void setWaveId(int waveId);
	Wave();
	Wave(std::vector<std::tuple <int, EnemyDesigner*,std::string>> enemiesVector,int waveId);
	void setEnemies(std::vector<std::tuple <int, EnemyDesigner*, std::string>> enemiesVector);
	void addEnemy(int numberOfEnemies, EnemyDesigner* enemy, std::string enemyName);
	void clearEnemies();
	std::vector <std::tuple <int, EnemyDesigner*, std::string>> getEnemiesVector();

protected:
	int waveId;
	std::vector<std::tuple <int,EnemyDesigner*,std::string>> enemiesVector;
};

