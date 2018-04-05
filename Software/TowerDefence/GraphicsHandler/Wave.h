#pragma once
#include "EnemyDesigner.h"
#include <vector>
class Wave
{
public:
	int getWaveId();
protected:
	int waveId;
	std::vector <int,EnemyDesigner*> vec;


};

