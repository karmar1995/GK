#pragma once
#include "Level.h"

Level::Level(std::vector <Wave> vectorOfWaves,std::string mapName) {
	this->vectorOfWaves=vectorOfWaves;
	this->mapName = mapName;
}
std::string Level::getMapName() {
	return this->mapName;
}