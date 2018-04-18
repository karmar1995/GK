#include "Wave.h"
int Wave::getWaveId() {
	return this->waveId;
}
Wave::Wave() {};


Wave::Wave(std::vector<std::tuple <int, EnemyDesigner*>> enemiesVector) {
	this->enemiesVector = enemiesVector;
}

void Wave::addEnemy(int numberOfEnemy, EnemyDesigner* enemy) {

	this->enemiesVector.push_back(std::make_tuple(numberOfEnemy, enemy));
}

void Wave::setEnemies(std::vector<std::tuple <int, EnemyDesigner*>> enemiesVector) {

	this->enemiesVector = enemiesVector;
}

void Wave::clearEnemies() {
	this->enemiesVector.clear();
}