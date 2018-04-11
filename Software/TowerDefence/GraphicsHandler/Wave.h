#pragma once
#include "EnemyDesigner.h"
#include <vector>
class Wave
{
public:
	int getWaveId();
	Wave(std::vector <int, EnemyDesigner*> enemyVector);
protected:
	int waveId=0;
	std::vector <int,EnemyDesigner*> enemyVector;


};

