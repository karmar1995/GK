#pragma once
#include <string>
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Level.h"
#include "Wave.h"
#include "EnemyDesigner.h"
#include "rapidxml.hpp"
#include <memory>
#include "rapidxml_utils.hpp"

using namespace rapidxml;
class ConfigurationManager {
private:
	std::string configFile;
	std::vector<Level> levels;
public:
	ConfigurationManager(std::string file="config.txt");
	void readConfiguration();
	std::vector<Level> getLevels();
	int numberOfLevels;
};