#include "Wave.h"

///
///@brief getter for wave id
///
int Wave::getWaveId() {
	return this->waveId;
}
///
///@brief Constructor
///
Wave::Wave() {};

///
///@brief Constructor with parameters
///@param vector of tuples representing enemies, their names and numbers
///@param wave's id
///
Wave::Wave(std::vector<std::tuple <int, EnemyDesigner*,std::string>> enemiesVector, int waveId) {
	this->enemiesVector = enemiesVector;
}
///
///@brief method adding enemies
///@param number of enemies
///@param pointer to enemy
///@param name of enemy
///
void Wave::addEnemy(int numberOfEnemy, EnemyDesigner* enemy,std::string enemyName) {

	this->enemiesVector.push_back(std::make_tuple(numberOfEnemy, enemy, enemyName));
}
///
///@brief method for setting enemy
///@param vector of tuples (number of enemies, pointer to enemy, name of enemy
///
void Wave::setEnemies(std::vector<std::tuple <int, EnemyDesigner*, std::string>> enemiesVector) {

	this->enemiesVector = enemiesVector;
}
///
///@brief method for clearing vector of enemies
///
void Wave::clearEnemies() {
	this->enemiesVector.clear();
}
///
///@brief getter for enemies vector
///
std::vector <std::tuple <int, EnemyDesigner*, std::string>> Wave::getEnemiesVector() {
	return this->enemiesVector;
}
///
///@brief setter for wave's ID
///@param wave's id
///
void Wave::setWaveId(int waveId) {
	this->waveId = waveId;
}