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

///
///@brief Class responsible for reading game's properties from xml file
///
class ConfigurationManager {
private:
	std::string configFile= "config.xml";  //xml file's name
	std::vector<Level> levels; // vector representing game's levels
public:
	ConfigurationManager(std::string file= "config.xml");
	void readConfiguration();
	std::vector<Level> getLevels();
	int numberOfLevels;
};