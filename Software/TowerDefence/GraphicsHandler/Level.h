#pragma once
#include "Wave.h"

class Level
{
public:
	std::string getMapName();
	Level(std::vector <Wave> vectorOfWaves,std::string mapName);
protected:

	std::string mapName;
	std::vector <Wave> vectorOfWaves;


};

