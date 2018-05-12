#pragma once
#include "Wave.h"
#include <vector>

class Level
{
public:
	std::string getMapName();
	Level();
	Level(std::vector <Wave> vectorOfWaves,std::string mapName);
	void setMapName(std::string mapName);
	void setWaves(std::vector <Wave> vectorOfWaves);
	void clearWaves();
	std::vector <Wave>  getWaves();
	void addWave(Wave wave);
protected:
	std::string mapName;
	std::vector <Wave> vectorOfWaves;
};

