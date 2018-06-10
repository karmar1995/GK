#include "ConfigurationManager.h"
using namespace std;


///@brief constructor 
///
///@param config file name
///
ConfigurationManager::ConfigurationManager(std::string configFile) {
	this->configFile = configFile;
};

///@brief getter for vector of levels 
//@returns vector of levels
///
std::vector<Level> ConfigurationManager::getLevels() {
	return this->levels;
}


///@brief configuration reader
///Method reads configuration from specified file. It uses rapidxml library 
///
void ConfigurationManager::readConfiguration() {

	try{
		rapidxml::file<> xmlFile("config.xml"); 
		xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		xml_node<> * root_node;
		root_node = doc.first_node("first");
		int i = 0;
		for (xml_node<> * level_node = root_node->first_node("level"); level_node; level_node = level_node->next_sibling())
		{
			Level level;
			xml_node<> * map_node = level_node->first_node("map");
			level.setMapName(map_node->value());

			for (xml_node<> * wave_node = level_node->first_node("wave"); wave_node; wave_node = wave_node->next_sibling())
			{
				Wave wave;
				wave.setWaveId(i);
				EnemyDesigner *enemy = nullptr;
				xml_node<> * birdNode;
				xml_node<> * zombieNode;
				xml_node<> * snakeNode;
				xml_node<> * vampireNode;

				birdNode = wave_node->first_node("bird");
				zombieNode = wave_node->first_node("zombie");
				snakeNode = wave_node->first_node("snake");
				vampireNode = wave_node->first_node("vampire");
				wave.addEnemy(atoi(birdNode->value()), enemy,"bird");
				wave.addEnemy(atoi(zombieNode->value()), enemy,"zombie");
				wave.addEnemy(atoi(snakeNode->value()), enemy,"snake");
				wave.addEnemy(atoi(vampireNode->value()), enemy,"vampire");
				level.addWave(wave);
				i++;
		}
		levels.push_back(level);
		i = 0;
	}
	}
	catch (exception e) {
		Level level;
		Wave wave;
		EnemyDesigner *enemy = nullptr;
		wave.addEnemy(1, enemy, "bird");
		wave.addEnemy(1, enemy, "zombie");
		wave.addEnemy(1, enemy, "snake");
		wave.addEnemy(1, enemy, "vampire");
		level.addWave(wave);
		levels.push_back(level);
	}
}

	

