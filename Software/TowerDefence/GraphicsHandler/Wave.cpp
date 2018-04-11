#pragma once
#include "Wave.h"
int Wave::getWaveId() {
	return this->waveId;
}
Wave::Wave(std::vector <int, EnemyDesigner*> enemyVector) {
	this->enemyVector = enemyVector;
	this->waveId++;
}