#pragma once
#include "Wave.h"
#include <vector>

///
///@brief Class representing levels in game
///
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
	std::string mapName; //string representing map name
	std::vector <Wave> vectorOfWaves; //vector representing enemies waves
};

