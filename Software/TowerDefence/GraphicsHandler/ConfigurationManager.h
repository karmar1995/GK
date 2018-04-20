#pragma once
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Level.h"
#include "Wave.h"
#include "EnemyDesigner.h"
#include "json.hpp"
using json = nlohmann::json;
class ConfigurationManager {
private:
	std::string configFile;
	std::vector<Level> levels;
public:
	ConfigurationManager(std::string file="config3.txt");
	void readConfiguration(std::string file);
	std::vector<Level> getLevels();
	int numberOfLevels;
	std::string temporary;

};