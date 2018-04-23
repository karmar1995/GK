#include "Level.h"

Level::Level() {};

Level::Level(std::vector <Wave> vectorOfWaves,std::string mapName) {
	this->vectorOfWaves=vectorOfWaves;
	this->mapName = mapName;
}

std::string Level::getMapName() {
	return this->mapName;
}

void Level::setMapName(std::string mapName) {
	this->mapName = mapName;
}

void Level::setWaves(std::vector <Wave> vectorOfWaves) {
	this->vectorOfWaves = vectorOfWaves;
}

void Level::clearWaves() {
	this->vectorOfWaves.clear();
}

std::vector <Wave> Level::getWaves() {
	return this->vectorOfWaves;
}