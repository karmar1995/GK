#include "Wave.h"
int Wave::getWaveId() {
	return this->waveId;
}
Wave::Wave() {};


Wave::Wave(std::vector<std::tuple <int, EnemyDesigner*,std::string>> enemiesVector, int waveId) {
	this->enemiesVector = enemiesVector;
}

void Wave::addEnemy(int numberOfEnemy, EnemyDesigner* enemy,std::string enemyName) {

	this->enemiesVector.push_back(std::make_tuple(numberOfEnemy, enemy, enemyName));
}

void Wave::setEnemies(std::vector<std::tuple <int, EnemyDesigner*, std::string>> enemiesVector) {

	this->enemiesVector = enemiesVector;
}

void Wave::clearEnemies() {
	this->enemiesVector.clear();
}

std::vector <std::tuple <int, EnemyDesigner*, std::string>> Wave::getEnemiesVector() {
	return this->enemiesVector;
}

void Wave::setWaveId(int waveId) {
	this->waveId = waveId;
}