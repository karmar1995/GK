#pragma once
#include "Wave.h"

class Level
{
public:
	std::string getMapName();

protected:
	std::string mapName;
	std::vector <Wave> vectorOfWaves;


};

