#include "Level.h"

Level::Level() {};

///
///@brief constructor 
///
///Method checks if shoot can be done, i.e. checks time interval from last shoot and compares range with distance
///If shoot is possible, bullet object is created
///@param  vector of waves
///@param map's name
///
Level::Level(std::vector <Wave> vectorOfWaves,std::string mapName) {
	this->vectorOfWaves=vectorOfWaves;
	this->mapName = mapName;
}


///
///@brief getter for map name
//@returns map's name
///
std::string Level::getMapName() {
	return this->mapName;
}
///
///@brief setter for map name 
///
///@param map name
///
void Level::setMapName(std::string mapName) {
	this->mapName = mapName;
}
///
///@brief  setter for map waves  
///
///@param vector of waves
///
void Level::setWaves(std::vector <Wave> vectorOfWaves) {
	this->vectorOfWaves = vectorOfWaves;
}
///
///@brief method for clearing vector of waves 
///
///Method clears vector from current waves
///
void Level::clearWaves() {
	this->vectorOfWaves.clear();
}

///
///@brief getter for waves 
//@returns vector of waves
///
std::vector <Wave> Level::getWaves() {
	return this->vectorOfWaves;
}

///
///@brief method for adding waves to vector 
///
///Method adds wave to vector of wave
///@param  Wave of enemiess
///
void Level::addWave(Wave wave) {
	this->vectorOfWaves.push_back(wave);
}